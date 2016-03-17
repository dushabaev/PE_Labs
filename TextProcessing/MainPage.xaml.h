//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

using namespace Platform;
using namespace Windows::Storage;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

namespace TextProcessing
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	//public delegate void Action(Plant^ obj);

	public ref class MainPage sealed
	{
	public:
		MainPage();
		property IVector<String^>^ Class;
		property IVector<String^>^ Division;
		property IVector<String^>^ Family;
		property IVector<String^>^ Genus;
		property IVector<String^>^ Kingdom;
		property IVector<String^>^ Order;

		property IVector<Plant^>^ Plants;
		
	private:
		EventRegistrationToken ActionBtnToken;
		void InitComboBoxes();
		Vector<String^>^ LoadData(const wchar_t* path);

		template<typename T>
		static T WaitForAsync(IAsyncOperation<T>^ action)
		{
			while (action->Status == AsyncStatus::Started)
				CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
			return action->GetResults();
		}
		
		static std::wstring data(const wchar_t* file)
		{
			static std::wstring folder = L"ms-appx:///Assets/plants/", ext = L".txt";
			return folder + file + ext;
		}
		
		Plant^ DataToPlant();
		void PlantToData(Plant^ plant);

		//void ComboBox_DataContextChanged(FrameworkElement^ sender, DataContextChangedEventArgs^ args);
		void ComboBox_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void DeleteButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void EditButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Grid_RightTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs^ e);
		
		void ActionBtnAdd_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ActionBtnApply_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void SaveBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OpenBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
