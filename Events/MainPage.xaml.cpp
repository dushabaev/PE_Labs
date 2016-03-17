//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <numeric>
#include <functional>
#include <algorithm>

using namespace Events;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::System;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	Items = ref new Vector<AdjustmentItem^>();
	InitializeComponent();
}


void Events::MainPage::SaveBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void Events::MainPage::OpenBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void Events::MainPage::Grid_RightTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs^ e)
{
	auto senderElement = dynamic_cast<FrameworkElement^>(sender);
	FlyoutBase::GetAttachedFlyout(senderElement)->ShowAt(dynamic_cast<FrameworkElement^>(e->OriginalSource));
}


void Events::MainPage::EditButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto item = dynamic_cast<AdjustmentItem^>(dynamic_cast<FrameworkElement^>(e->OriginalSource)->DataContext);
	ItemView->SelectedValue = item;
	ItemView->IsEnabled = false;

	ItemToData(item);

	ActionBtn->Click -= this->ActionBtnToken;
	this->ActionBtnToken = ActionBtn->Click += ref new RoutedEventHandler(this, &MainPage::ActionBtnApply_Click);
	ActionBtn->Content = L"APPLY";
}


void Events::MainPage::DeleteButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto item = dynamic_cast<AdjustmentItem^>(dynamic_cast<FrameworkElement^>(e->OriginalSource)->DataContext);
	auto it = std::find(begin(this->Items), end(this->Items), item);
	auto index = std::distance(begin(this->Items), it);

	this->Items->RemoveAt(index);
}


void Events::MainPage::ActionBtnAdd_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (TitleBox->Text->IsEmpty())
	{
		auto msgDlg = ref new Windows::UI::Popups::MessageDialog("Title can't be empty.\nPlease fill it and try again.", "Title is empty");
		msgDlg->ShowAsync();
	}
	else {
		this->Items->Append(this->DataToItem());
		TitleBox->Text = L"";
		CountBox->Text = "";
		PriceBox->Text = "";
		TitleBox->Focus(Windows::UI::Xaml::FocusState::Programmatic);
	}
}

void Events::MainPage::ActionBtnApply_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (TitleBox->Text->IsEmpty())
	{
		auto msgDlg = ref new Windows::UI::Popups::MessageDialog("Title can't be empty.\nPlease fill it and try again.", "Title is empty");
		msgDlg->ShowAsync();
	}
	else {
		auto index = this->ItemView->SelectedIndex;
		this->Items->SetAt(index, this->DataToItem());
		ItemView->IsEnabled = true;

		TitleBox->Text = L"";
		CountBox->Text = "";
		PriceBox->Text = "";
		TitleBox->Focus(Windows::UI::Xaml::FocusState::Programmatic);
		ActionBtn->Click -= this->ActionBtnToken;
		this->ActionBtnToken = ActionBtn->Click += ref new RoutedEventHandler(this, &MainPage::ActionBtnAdd_Click);
		ActionBtn->Content = L"ADD";
	}
}

AdjustmentItem^ MainPage::DataToItem()
{
	return ref new AdjustmentItem(
		TitleBox->Text,
		_wtof(PriceBox->Text->Data()),
		_wtof(CountBox->Text->Data())		
	);
}

void MainPage::ItemToData(AdjustmentItem^ item)
{
	TitleBox->Text = item->Title;
	CountBox->Text = item->Count.ToString();
	PriceBox->Text = item->Price.ToString();
}

void Events::MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->ActionBtnToken = (ActionBtn->Click += ref new RoutedEventHandler(this, &MainPage::ActionBtnAdd_Click));
}


void Events::MainPage::ItemView_ContainerContentChanging(Windows::UI::Xaml::Controls::ListViewBase^ sender, Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs^ args)
{
	recalculate_price();
}


void Events::MainPage::NumberBox_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto box = dynamic_cast<TextBox^>(sender);
	auto str = std::wstring(box->Text->Data());
	auto rubbish = std::remove_if(str.begin(), str.end(), [](wchar_t ch) {return !iswdigit(ch); });
	int pos = box->SelectionStart;

	str.erase(rubbish, str.end());
	box->Text = ref new String(str.c_str());
	box->SelectionStart = pos;
}


void Events::MainPage::Page_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	static bool handled{ false };
	if (!handled) {
		switch (e->Key)
		{
		case VirtualKey::Enter:
			if (ItemView->IsEnabled)
				ActionBtnAdd_Click(sender, e);
			else
				ActionBtnApply_Click(sender, e);
			handled = true;
		}
	}
	else
		handled = false;
}

void Events::MainPage::recalculate_price() {
	float64 price = std::accumulate(begin(Items), end(Items), 0.0,
		[](double a, AdjustmentItem^ b) {return a + b->Price*b->Count; }
	);
	price += price*_wtof(Tax->Text->Data()) / 100.0;
	this->Total->Text = price.ToString();
}

void Events::MainPage::Tax_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	NumberBox_TextChanged(sender, e);
	recalculate_price();
}
