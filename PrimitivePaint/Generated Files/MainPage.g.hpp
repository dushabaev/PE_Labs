﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BINDING_DEBUG_OUTPUT
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
#endif

#include "MainPage.xaml.h"

void ::PrimitivePaint::MainPage::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///MainPage.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}

void ::PrimitivePaint::MainPage::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
        case 1:
            {
                this->New = safe_cast<::Windows::UI::Xaml::Controls::AppBarButton^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::AppBarButton^>(this->New))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::PrimitivePaint::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::New_Click);
            }
            break;
        case 2:
            {
                this->Open = safe_cast<::Windows::UI::Xaml::Controls::AppBarButton^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::AppBarButton^>(this->Open))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::PrimitivePaint::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::Open_Click);
            }
            break;
        case 3:
            {
                this->Save = safe_cast<::Windows::UI::Xaml::Controls::AppBarButton^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::AppBarButton^>(this->Save))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::PrimitivePaint::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::Save_Click);
            }
            break;
        case 4:
            {
                this->Field = safe_cast<::Windows::UI::Xaml::Controls::Canvas^>(__target);
            }
            break;
        case 5:
            {
                this->Size = safe_cast<::Windows::UI::Xaml::Controls::ComboBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::ComboBox^>(this->Size))->SelectionChanged += ref new ::Windows::UI::Xaml::Controls::SelectionChangedEventHandler(this, (void (::PrimitivePaint::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::SelectionChangedEventArgs^))&MainPage::Size_SelectionChanged);
            }
            break;
        case 6:
            {
                this->Colour = safe_cast<::Windows::UI::Xaml::Controls::ComboBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::ComboBox^>(this->Colour))->SelectionChanged += ref new ::Windows::UI::Xaml::Controls::SelectionChangedEventHandler(this, (void (::PrimitivePaint::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::SelectionChangedEventArgs^))&MainPage::Colour_SelectionChanged);
            }
            break;
        case 7:
            {
                this->ColourFill = safe_cast<::Windows::UI::Xaml::Controls::ComboBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::ComboBox^>(this->ColourFill))->SelectionChanged += ref new ::Windows::UI::Xaml::Controls::SelectionChangedEventHandler(this, (void (::PrimitivePaint::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::SelectionChangedEventArgs^))&MainPage::ColourFill_SelectionChanged);
            }
            break;
        case 8:
            {
                ::Windows::UI::Xaml::Controls::Button^ element8 = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(element8))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::PrimitivePaint::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::PencilButton_Click);
            }
            break;
        case 9:
            {
                ::Windows::UI::Xaml::Controls::Button^ element9 = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(element9))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::PrimitivePaint::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::LineButtn_Click);
            }
            break;
        case 10:
            {
                ::Windows::UI::Xaml::Controls::Button^ element10 = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(element10))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::PrimitivePaint::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::RectangleButton_Click);
            }
            break;
        case 11:
            {
                ::Windows::UI::Xaml::Controls::Button^ element11 = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(element11))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::PrimitivePaint::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::EllipseButton_Click);
            }
            break;
        case 12:
            {
                ::Windows::UI::Xaml::Controls::Button^ element12 = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(element12))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::PrimitivePaint::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::EraserButton_Click);
            }
            break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::PrimitivePaint::MainPage::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    __connectionId;         // unreferenced
    __target;               // unreferenced
    return nullptr;
}


