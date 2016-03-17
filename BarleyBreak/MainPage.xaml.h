//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Controls;
using namespace Platform;
using namespace Platform::Collections;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace BarleyBreak
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	using Point = std::pair<short, short>;	
	static Color GradientCell[] { 
		ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00),
		ColorHelper::FromArgb(0xFF, 0x12, 0x12, 0x12),
		ColorHelper::FromArgb(0xFF, 0x00, 0x00, 0x00),
		ColorHelper::FromArgb(0xFF, 0x36, 0x36, 0x36),
		ColorHelper::FromArgb(0xFF, 0x48, 0x48, 0x48),
		ColorHelper::FromArgb(0xFF, 0x5B, 0x5B, 0x5B),
		ColorHelper::FromArgb(0xFF, 0x6D, 0x6D, 0x6D),
		ColorHelper::FromArgb(0xFF, 0x7F, 0x7F, 0x7F),
		ColorHelper::FromArgb(0xFF, 0x91, 0x91, 0x91),
		ColorHelper::FromArgb(0xFF, 0xA3, 0xA3, 0xA3),
		ColorHelper::FromArgb(0xFF, 0xB6, 0xB6, 0xB6),
		ColorHelper::FromArgb(0xFF, 0xC8, 0xC8, 0xC8),
		ColorHelper::FromArgb(0xFF, 0xDA, 0xDA, 0xDA),
		ColorHelper::FromArgb(0xFF, 0xEC, 0xEC, 0xEC),
		ColorHelper::FromArgb(0xFF, 0xFF, 0xFF, 0xFF)
	};
	
	public ref class MainPage sealed 
	{
	public:
		MainPage();

	private:		
		Point empty;
		Grid^ matrix[4][4];

		DispatcherTimer^ timer;
		unsigned int hours, minutes, seconds, moves;

		void update_blocks();
		void reset_blocks();

		void InitMatrix();
		void Shuffle(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Shuffle();

		std::vector<Point> get_available();
		void move(int col, int row);

		static Color GetColor(int dist_sq){
			switch (dist_sq)
			{
			case 0:
				return Colors::Black;
			case 1:
				return ColorHelper::FromArgb(0xFF, 0x1C, 0x1C, 0x1C);
			case 2:
				return ColorHelper::FromArgb(0xFF, 0x38, 0x38, 0x38);
			case 4:
				return ColorHelper::FromArgb(0xFF, 0x55, 0x55, 0x55);
			case 5:
				return ColorHelper::FromArgb(0xFF, 0x71, 0x71, 0x71);
			case 8:
				return ColorHelper::FromArgb(0xFF, 0x8D, 0x8D, 0x8D);
			case 9:
				return ColorHelper::FromArgb(0xFF, 0xAA, 0xAA, 0xAA);
			case 10:
				return ColorHelper::FromArgb(0xFF, 0xC6, 0xC6, 0xC6);
			case 13:
				return ColorHelper::FromArgb(0xFF, 0xE2, 0xE2, 0xE2);
			case 18:
				return ColorHelper::FromArgb(0xFF, 0xFF, 0xFF, 0xFF);
			default:
				return Colors::Red;
			}
		}

		bool is_valid(Point point) { return point.first >= 0 && point.first < 4 && point.second >= 0 && point.second < 4; }
		long distance_sq(int x1, int y1, int x2, int y2) { return pow(x2 - x1, 2) + pow(y2 - y1, 2); }
		long distance_sq(int col, int row, int value) { return distance_sq(col, row, value % 4, value / 4); }
		
		bool solved();

		void Field_ManipulationDelta(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
		void Field_ManipulationCompleted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
		void Field_ManipulationStarted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e);
		void OnTick(Platform::Object ^sender, Platform::Object ^args);
	};
}
