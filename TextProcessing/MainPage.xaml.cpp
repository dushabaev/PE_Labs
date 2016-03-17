//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <algorithm>

using namespace TextProcessing;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace concurrency;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	this->Plants = ref new Vector<Plant^>;// {ref new Plant(L"title!", L"king", L"", L"", L"", L"", L"genus")};
	this->InitComboBoxes();

	InitializeComponent();
}

Vector<String^>^ MainPage::LoadData(const wchar_t* path)
{
	using SF = StorageFile;
	auto file = WaitForAsync(SF::GetFileFromApplicationUriAsync(ref new Uri(ref new String(path))));
	auto lines = WaitForAsync(FileIO::ReadLinesAsync(file));
	return ref new Vector<String^>(begin(lines), end(lines));
}

void MainPage::InitComboBoxes()
{
	this->Class = this->LoadData(data(L"class").c_str());
	this->Division = this->LoadData(data(L"division").c_str());
	this->Family = this->LoadData(data(L"family").c_str());
	this->Genus = this->LoadData(data(L"genus").c_str());
	this->Kingdom = this->LoadData(data(L"kingdom").c_str());
	this->Order = this->LoadData(data(L"order").c_str());
}

//void TextProcessing::MainPage::ComboBox_DataContextChanged(Windows::UI::Xaml::FrameworkElement^ sender, Windows::UI::Xaml::DataContextChangedEventArgs^ args)
//{
//	dynamic_cast<ComboBox^>(sender)->SelectedIndex = 0;
//}


void TextProcessing::MainPage::ComboBox_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	dynamic_cast<ComboBox^>(sender)->SelectedIndex = 0;
}


void TextProcessing::MainPage::DeleteButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto plant = dynamic_cast<Plant^>(dynamic_cast<FrameworkElement^>(e->OriginalSource)->DataContext);
	auto it = std::find(begin(this->Plants), end(this->Plants), plant);
	auto index = std::distance(begin(this->Plants), it);
	
	this->Plants->RemoveAt(index);
}


void TextProcessing::MainPage::EditButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto plant = dynamic_cast<Plant^>(dynamic_cast<FrameworkElement^>(e->OriginalSource)->DataContext);
	PlantView->SelectedValue = plant;
	PlantView->IsEnabled = false;
	
	PlantToData(plant);

	ActionBtn->Click -= this->ActionBtnToken;
	this->ActionBtnToken = ActionBtn->Click += ref new RoutedEventHandler(this, &MainPage::ActionBtnApply_Click);
	ActionBtn->Content = L"APPLY";
}

void TextProcessing::MainPage::Grid_RightTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs^ e)
{
	auto senderElement = dynamic_cast<FrameworkElement^>(sender);
	FlyoutBase::GetAttachedFlyout(senderElement)->ShowAt(dynamic_cast<FrameworkElement^>(e->OriginalSource));
}

void TextProcessing::MainPage::ActionBtnAdd_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (TitleBox->Text->IsEmpty())
	{
		auto msgDlg = ref new Windows::UI::Popups::MessageDialog("Title can't be empty.\nPlease fill it and try again.", "Title is empty");
		msgDlg->ShowAsync();
	}
	else {
		this->Plants->Append(this->DataToPlant());
		TitleBox->Text = L"";
		TitleBox->Focus(Windows::UI::Xaml::FocusState::Programmatic);
	}
}

void TextProcessing::MainPage::ActionBtnApply_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (TitleBox->Text->IsEmpty())
	{
		auto msgDlg = ref new Windows::UI::Popups::MessageDialog("Title can't be empty.\nPlease fill it and try again.", "Title is empty");
		msgDlg->ShowAsync();
	}
	else {
		auto index = this->PlantView->SelectedIndex;
		this->Plants->SetAt(index, this->DataToPlant());
		PlantView->IsEnabled = true;

		TitleBox->Text = L"";
		TitleBox->Focus(Windows::UI::Xaml::FocusState::Programmatic);

		ActionBtn->Click -= this->ActionBtnToken;
		this->ActionBtnToken = ActionBtn->Click += ref new RoutedEventHandler(this, &MainPage::ActionBtnAdd_Click);
		ActionBtn->Content = L"ADD";
	}
}

Plant^ MainPage::DataToPlant()
{
	return ref new Plant(
		TitleBox->Text,
		dynamic_cast<String^>(KingdomBox->SelectedValue),
		dynamic_cast<String^>(DivisionBox->SelectedValue),
		dynamic_cast<String^>(ClassBox->SelectedValue),
		dynamic_cast<String^>(OrderBox->SelectedValue),
		dynamic_cast<String^>(FamilyBox->SelectedValue),
		dynamic_cast<String^>(GenusBox->SelectedValue)
	);
}

void MainPage::PlantToData(Plant^ plant)
{
	TitleBox->Text = plant->Title;
	ClassBox->SelectedItem = plant->Class;
	DivisionBox->SelectedItem = plant->Division;
	FamilyBox->SelectedItem = plant->Family;
	GenusBox->SelectedItem = plant->Genus;
	KingdomBox->SelectedItem = plant->Kingdom;
	OrderBox->SelectedItem = plant->Order;
}


void TextProcessing::MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->ActionBtnToken = (ActionBtn->Click += ref new RoutedEventHandler(this, &MainPage::ActionBtnAdd_Click));
}


void TextProcessing::MainPage::SaveBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto picker = ref new FileSavePicker();
	picker->FileTypeChoices->Insert("Plain Text", ref new Vector<String^>{ ".txt" });
	picker->SuggestedFileName = "Collection";
	picker->SuggestedStartLocation = PickerLocationId::Desktop;

	create_task(picker->PickSaveFileAsync()).then([this](StorageFile^ file)
	{
		if (file == nullptr) return;
		auto plants = ref new Vector<String^>();
		for (auto&& plant : this->Plants)
		{
			plants->Append(plant->Title);
			plants->Append(plant->Kingdom);
			plants->Append(plant->Division);
			plants->Append(plant->Class);
			plants->Append(plant->Order);
			plants->Append(plant->Family);
			plants->Append(plant->Genus);
		}
		CachedFileManager::DeferUpdates(file);
		create_task(FileIO::WriteLinesAsync(file, plants)).then([file]()
		{
			create_task(CachedFileManager::CompleteUpdatesAsync(file)).then([](Windows::Storage::Provider::FileUpdateStatus status)
			{
				Windows::UI::Popups::MessageDialog^ dlg;
				switch (status)
				{
				case Windows::Storage::Provider::FileUpdateStatus::Complete:
					dlg = ref new Windows::UI::Popups::MessageDialog("", "File was saved");
					dlg->ShowAsync();
					break;
				default:
					dlg = ref new Windows::UI::Popups::MessageDialog("", "File couldn't be saved");
					dlg->ShowAsync();
					break;
				}
			});
		});
	});
}

void TextProcessing::MainPage::OpenBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto picker = ref new FileOpenPicker();
	picker->FileTypeFilter->Append(L".txt");
	picker->SuggestedStartLocation = PickerLocationId::Desktop;
	create_task(picker->PickSingleFileAsync()).then([this](StorageFile^ file)
	{
		if (file == nullptr) return;
		create_task(FileIO::ReadLinesAsync(file)).then([this](IVector<String^>^ lines)
		{
			Plants->Clear();
			for (size_t i = 0; i < lines->Size; i += 7)
			{
				Plants->Append(
					ref new Plant(
						lines->GetAt(i),
						lines->GetAt(i + 1),
						lines->GetAt(i + 2),
						lines->GetAt(i + 3),
						lines->GetAt(i + 4),
						lines->GetAt(i + 5),
						lines->GetAt(i + 6)
						)
					);
			}
		});			
		}
			
	);
}
