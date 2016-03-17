//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Shapes;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace PrimitivePaint
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		Color StrokeColor, FillColor;
		double StrokeThickness;
		Shape^ DrawingShape;

		EventRegistrationToken PointerPressedToken;
		EventRegistrationToken PointerReleasedToken;
		EventRegistrationToken PointerMovedToken;

		void PencilButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void LineButtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void EllipseButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void RectangleButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		
		// Pencil events
		void OnPencilPressed(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
		void OnPencilReleased(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
		void OnPencilMoved(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
		
		// Line events
		void OnLinePressed(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
		void OnLineReleased(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
		void OnLineMoved(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
		
		// Ellipse events
		void OnEllipsePressed(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
		void OnEllipseReleased(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
		
		// Rectangel events
		void OnRectanglePressed(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
		void OnRectangleReleased(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
	
		void Colour_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void Size_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);

		// File buttons
		void New_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Open_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Save_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		// ProcessingEvents
		
		void OnPressed(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
		void OnMoved(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);

		template<typename T>
		double ProcessSizeChanging(double obj_size, double size, float point, short index, T func);

		void DeregisterTokens();
		void ColourFill_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void EraserButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnEraserPressed(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
		void OnEraserMoved(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e);
	};

	template<typename T>
	inline double MainPage::ProcessSizeChanging(double obj_size, double size, float point, short index, T func) {
		if (size < 0) {
			func(this->DrawingShape, point);
			dynamic_cast<Array<bool>^>(this->DrawingShape->Tag)->set(index, true);
			return obj_size + -size;
		}
		else if (dynamic_cast<Array<bool>^>(this->DrawingShape->Tag)->get(index)) {
			bool res = size < obj_size;
			auto val = size;
			if (res) {
				func(this->DrawingShape, point);
				val = obj_size - size;
			}
			dynamic_cast<Array<bool>^>(this->DrawingShape->Tag)->set(index, res);
			return val;
		}
		else
			return size;
	}
}
