//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace BarleyBreak;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Shapes;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

BarleyBreak::MainPage::MainPage() : empty{3,3}
{
	srand(time(0));	
	InitializeComponent();
	this->timer = ref new DispatcherTimer();

	TimeSpan t; t.Duration = 10000000; // one second
	timer->Interval = t;
	timer->Tick += ref new Windows::Foundation::EventHandler<Platform::Object ^>(this, &BarleyBreak::MainPage::OnTick);
	hours = minutes = seconds = moves = 0;
	

	for (int i = 0; i < 15; i++)
	{	
		auto rect = ref new Rectangle();
		rect->Fill = ref new SolidColorBrush(ColorHelper::FromArgb(0xFF, 0, 0, 0));

		auto text = ref new TextBlock();
		text->Text = (i+1).ToString();		
		text->Foreground = ref new SolidColorBrush(Colors::White);

		auto grid = ref new Grid();
		grid->RenderTransform = ref new TranslateTransform();

		grid->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &MainPage::Field_ManipulationDelta);
		grid->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &MainPage::Field_ManipulationCompleted);
		grid->ManipulationStarted += ref new ManipulationStartedEventHandler(this, &MainPage::Field_ManipulationStarted);

		grid->Children->Append(rect);
		grid->Children->Append(text);
		
		matrix[i / 4][i % 4] = grid;

		Field->SetRow(grid, i / 4);
		Field->SetColumn(grid, i % 4);

		Field->Children->Append(grid);
	}
	matrix[3][3] = nullptr;
	//Shuffle();
}

bool BarleyBreak::MainPage::solved()
{
	if (empty != std::make_pair(short(3), short(3))) return false;

	Grid^ curr = matrix[0][0];

	for (int i = 1; i < 15; ++i) {
		auto next = matrix[i / 4][i % 4];
		auto iter = next->Children->First(); iter->MoveNext();
		auto next_value = _wtoi(dynamic_cast<TextBlock^>(iter->Current)->Text->Data());

		iter = curr->Children->First(); iter->MoveNext();
		auto curr_value = _wtoi(dynamic_cast<TextBlock^>(iter->Current)->Text->Data());

		if (curr_value > next_value) 
			return false;

		curr = next;
	}
	return true;
}

void BarleyBreak::MainPage::Field_ManipulationDelta(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	auto transform = dynamic_cast<TranslateTransform^>(dynamic_cast<Grid^>(sender)->RenderTransform);
	
	transform->X += e->Delta.Translation.X;
	transform->Y += e->Delta.Translation.Y;
}

void BarleyBreak::MainPage::Field_ManipulationCompleted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{
	auto grid = dynamic_cast<Grid^>(sender);
	auto transform = dynamic_cast<TranslateTransform^>(grid->RenderTransform);
	
	transform->X = 0;
	transform->Y = 0;
	int x = e->Cumulative.Translation.X / 25;
	int y = e->Cumulative.Translation.Y / 25;
	
	x = (x < 0 ? -1 : x>0 ? 1 : 0);
	y = (y < 0 ? -1 : y>0 ? 1 : 0);
	
	Point source{ Field->GetColumn(grid), Field->GetRow(grid) };
	Point target{
		source.first + x,
		source.second + y
	};

	if (x*y == 0 && target == this->empty) {
		move(source.first, source.second);
		if (solved()) {
			timer->Stop();
			std::wstring str = L"Moves: ";
			str += moves.ToString()->Data(); str += L"\nTime elapsed: ";
			str += HoursBlock->Text->Data(); str += L":";
			str += MinutesBlock->Text->Data(); str += L":";
			str += SecondsBlock->Text->Data();

			auto dlg = ref new Windows::UI::Popups::MessageDialog(ref new String(str.c_str()), "Completed");
			dlg->ShowAsync();
		}
	}
}

void BarleyBreak::MainPage::Field_ManipulationStarted(Platform::Object ^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs ^ e)
{
	//throw ref new Platform::NotImplementedException();
}

std::vector<BarleyBreak::Point> BarleyBreak::MainPage::get_available()
{
	std::vector<Point> points{ {empty.first - 1, empty.second}, {empty.first, empty.second - 1}, {empty.first + 1, empty.second}, {empty.first, empty.second + 1} };
	std::vector<Point> v;
	for (auto& point : points)
		if (is_valid(point))
			v.push_back(point);
	return v;
}

void BarleyBreak::MainPage::move(int col, int row) {	
	auto grid = matrix[row][col];

	auto iter = grid->Children->First();
	auto rect = dynamic_cast<Rectangle^>(iter->Current);

	iter->MoveNext();
	TextBlock^ txt = dynamic_cast<TextBlock^>(iter->Current);
	auto value = _wtoi(txt->Text->Data())-1;

	auto clr = GetColor(distance_sq(empty.first, empty.second, value));
	rect->Fill = ref new SolidColorBrush(clr);
	
	txt->Foreground = ref new SolidColorBrush(ColorHelper::FromArgb(clr.A, (byte)~clr.R, (byte)~clr.G, (byte)~clr.B));
	
	Field->SetColumn(grid, empty.first);
	Field->SetRow(grid, empty.second);

	std::swap(grid, matrix[empty.second][empty.first]);
	this->empty = std::make_pair(col, row);

	++moves;
}

void BarleyBreak::MainPage::update_blocks()
{
	HoursBlock->Text = (seconds / 3600).ToString();
	MinutesBlock->Text = ((seconds % 3600) / 60).ToString();
	SecondsBlock->Text = (seconds % 60).ToString();
}

void BarleyBreak::MainPage::reset_blocks()
{
	hours = minutes = seconds = 0;
	update_blocks();
}

void BarleyBreak::MainPage::Shuffle(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Shuffle();
	ActionBtn->Icon = ref new SymbolIcon(Symbol::Refresh);
	ActionBtn->Label = "Restart";
}

void BarleyBreak::MainPage::Shuffle() {
	std::vector<Point> available;
	for (int i = 0; i < 1000; ++i)
	{
		available = get_available();
		auto point = available[rand() % available.size()];
		auto next = this->empty;
		int len;

		if (rand() % 2) { // Y
			if (rand() % 2) { // UP
				len = empty.second;
				if (len) len -= (rand() % empty.second);
				else continue;
				--next.second;
				for (size_t i = 0; i < len; ++i, --next.second)
					this->move(next.first, next.second);
			}
			else { // DOWN			
				len = 3 - empty.second;
				if (len) len -= (rand() % len);
				else continue;
				++next.second;
				for (size_t i = 0; i < len; ++i, ++next.second)
					this->move(next.first, next.second);
			}
		}
		else { // X
			if (rand() % 2) { // RIGHT
				len = 3 - empty.first;
				if (len) len -= (rand() % len);
				else continue;
				++next.first;
				for (size_t i = 0; i < len; ++i, ++next.first)
					this->move(next.first, next.second);
			}
			else { // LEFT
				len = empty.first;
				if (len) len -= (rand() % empty.first);
				else continue;
				--next.first;
				for (size_t i = 0; i < len; ++i, --next.first)
					this->move(next.first, next.second);
			}
		}
	}

	moves = 0;
	reset_blocks();

	timer->Start();
}

void BarleyBreak::MainPage::OnTick(Platform::Object ^sender, Platform::Object ^args)
{
	++seconds;
	update_blocks();
}
