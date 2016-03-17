//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace PrimitivePaint;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Shapes;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Input::Inking;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace concurrency;
// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage() : 
	StrokeColor(Windows::UI::Colors::Black), 
	FillColor(Colors::Black), 
	StrokeThickness(10), 
	DrawingShape()
{
	InitializeComponent();
	PointerPressedToken.Value = PointerMovedToken.Value = PointerReleasedToken.Value = 0;
}


void PrimitivePaint::MainPage::PencilButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	DeregisterTokens();
	
	PointerPressedToken = Field->PointerPressed += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnPencilPressed);
	PointerReleasedToken = Field->PointerReleased += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnPencilReleased);
	PointerMovedToken = Field->PointerMoved += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnPencilMoved);
}


void PrimitivePaint::MainPage::LineButtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	DeregisterTokens();

	PointerPressedToken = Field->PointerPressed += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnLinePressed);
	PointerReleasedToken = Field->PointerReleased += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnLineReleased);
	PointerMovedToken = Field->PointerMoved += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnLineMoved);
}


void PrimitivePaint::MainPage::EllipseButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	DeregisterTokens();

	PointerPressedToken = Field->PointerPressed += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnEllipsePressed);
	PointerReleasedToken = Field->PointerReleased += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnEllipseReleased);
	PointerMovedToken = Field->PointerMoved += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnMoved);
}


void PrimitivePaint::MainPage::RectangleButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	DeregisterTokens();

	PointerPressedToken = Field->PointerPressed += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnRectanglePressed);
	PointerReleasedToken = Field->PointerReleased += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnRectangleReleased);
	PointerMovedToken = Field->PointerMoved += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnMoved);
}

void PrimitivePaint::MainPage::OnPencilPressed(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	auto pline = ref new Polyline();
	pline->Points->Append(e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Position);
	pline->Stroke = ref new SolidColorBrush(StrokeColor);
	pline->StrokeThickness = StrokeThickness;
	//pline->FillRule = Windows::UI::Xaml::Media::FillRule::Nonzero;
	pline->StrokeMiterLimit = 0;
	//pline->Fill = ref new SolidColorBrush(FillColor);
	this->DrawingShape = pline;
	Field->Children->Append(this->DrawingShape);
	
	/*auto path = ref new Path();
	auto geometry = ref new PathGeometry();
	auto figure = ref new PathFigure();
	
	figure->StartPoint = e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Position;
	auto segment = ref new PolyBezierSegment();
	segment->Points->Append(figure->StartPoint);
	
	figure->Segments->Append(segment);
	geometry->Figures->Append(figure);
	
	path->Data = geometry;
	path->Stroke = ref new SolidColorBrush(Colors::Black);
	path->StrokeThickness = 10;

	this->DrawingShape = path;
	Field->Children->Append(this->DrawingShape);*/
	//throw ref new Platform::NotImplementedException();
}


void PrimitivePaint::MainPage::OnPencilReleased(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	//throw ref new Platform::NotImplementedException();
}


void PrimitivePaint::MainPage::OnPencilMoved(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	if (!e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Properties->IsLeftButtonPressed) return;
	
	auto pline = dynamic_cast<Polyline^>(this->DrawingShape);
	pline->Points->Append(e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Position);
	
	/*auto path = dynamic_cast<Path^>(this->DrawingShape);
	auto geometry = dynamic_cast<PathGeometry^>(path->Data);
	auto segment = dynamic_cast<PolyBezierSegment^>(geometry->Figures->GetAt(0)->Segments->GetAt(0));
	segment->Points->Append(e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Position);
*/
	//throw ref new Platform::NotImplementedException();
}


void PrimitivePaint::MainPage::OnLinePressed(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	auto line = ref new Line();
	auto point = e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Position;
	line->Stroke = ref new SolidColorBrush(this->StrokeColor);
	line->Fill = ref new SolidColorBrush(this->FillColor);

	line->StrokeThickness = this->StrokeThickness;
	line->X1 = point.X;
	line->Y1 = point.Y;
	line->X2 = point.X;
	line->Y2 = point.Y;
	Field->Children->Append(line);
	this->DrawingShape = line;
	//throw ref new Platform::NotImplementedException();
}


void PrimitivePaint::MainPage::OnLineReleased(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	//this->DrawingShape = nullptr;
	//throw ref new Platform::NotImplementedException();
}


void PrimitivePaint::MainPage::OnLineMoved(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	if (!e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Properties->IsLeftButtonPressed) return;
	auto point = e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Position;
	dynamic_cast<Line^>(this->DrawingShape)->X2 = point.X;
	dynamic_cast<Line^>(this->DrawingShape)->Y2 = point.Y;

	//throw ref new Platform::NotImplementedException();
}


void PrimitivePaint::MainPage::OnEllipsePressed(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	this->DrawingShape = ref new Windows::UI::Xaml::Shapes::Ellipse();
	OnPressed(sender, e);
}


void PrimitivePaint::MainPage::OnEllipseReleased(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	//throw ref new Platform::NotImplementedException();
}


void PrimitivePaint::MainPage::OnRectanglePressed(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	this->DrawingShape = ref new Windows::UI::Xaml::Shapes::Rectangle();
	OnPressed(sender, e);
}


void PrimitivePaint::MainPage::OnRectangleReleased(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	//throw ref new Platform::NotImplementedException();
}



void PrimitivePaint::MainPage::Colour_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	if (Field == nullptr) return;
	StrokeColor = dynamic_cast<SolidColorBrush^>(dynamic_cast<Windows::UI::Xaml::Shapes::Rectangle^>(dynamic_cast<ComboBoxItem^>(Colour->SelectedValue)->Content)->Fill)->Color;
}


void PrimitivePaint::MainPage::Size_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	if (Field == nullptr) return;	
	this->StrokeThickness = _wtof(dynamic_cast<Platform::String^>(dynamic_cast<ComboBoxItem^>(Size->SelectedValue)->Content)->Data());	
}


void PrimitivePaint::MainPage::New_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
}


void PrimitivePaint::MainPage::Open_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	/*auto picker = ref new FileOpenPicker();
	picker->FileTypeFilter->Append(L".drw");
	picker->SuggestedStartLocation = PickerLocationId::Desktop;

	create_task(picker->PickSingleFileAsync()).then([this](StorageFile^ file)
	{
		if (file == nullptr) return;
		create_task(file->OpenAsync(FileAccessMode::Read)).then([=](IRandomAccessStream^ stream) {
			Field->InkPresenter->StrokeContainer->LoadAsync(stream);
		});
	});*/
}


void PrimitivePaint::MainPage::Save_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto picker = ref new FileSavePicker();
	picker->FileTypeChoices->Insert("Plain Text", ref new Vector<String^>{ ".drw" });
	picker->SuggestedFileName = "Picture";
	picker->SuggestedStartLocation = PickerLocationId::Desktop;

	create_task(picker->PickSaveFileAsync()).then([this](StorageFile^ file)
	{
		if (file == nullptr) return;

		/*auto rtb = ref new RenderTargetBitmap();
		create_task(rtb->RenderAsync(Field)).then([=]() {
			auto img = ref new BitmapImage();
			create_task(rtb->GetPixelsAsync()).then([=](IBuffer^ buf) {
				create_task(file->OpenAsync(FileAccessMode::ReadWrite)).then([&](IRandomAccessStream^ stream) {
					
				});
			});
		});*/
		/*create_task(file->OpenAsync(FileAccessMode::ReadWrite)).then([=](IRandomAccessStream^ stream) {
			Field->InkPresenter->StrokeContainer->SaveAsync(stream);
		});*/
	});
}

void PrimitivePaint::MainPage::OnPressed(Platform::Object ^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^ e)
{
	auto point = e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Position;

	this->DrawingShape->Stroke = ref new SolidColorBrush(this->StrokeColor);
	this->DrawingShape->Fill = ref new SolidColorBrush(this->FillColor);
	this->DrawingShape->StrokeThickness = this->StrokeThickness;
	this->DrawingShape->Width = 0;
	this->DrawingShape->Height = 0;
	this->DrawingShape->Tag = ref new Array<bool>{ false, false };

	Field->SetLeft(this->DrawingShape, point.X);
	Field->SetTop(this->DrawingShape, point.Y);

	Field->Children->Append(this->DrawingShape);
}

void PrimitivePaint::MainPage::OnMoved(Platform::Object ^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^ e)
{
	if (!e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Properties->IsLeftButtonPressed) return;

	auto point = e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Position;
	float X = point.X, Y = point.Y;

	auto left = Field->GetLeft(this->DrawingShape);
	auto top = Field->GetTop(this->DrawingShape);
	auto width = X - left;
	auto height = Y - top;

	this->DrawingShape->Width = this->ProcessSizeChanging(this->DrawingShape->Width, width, X, 0, Field->SetLeft);
	this->DrawingShape->Height = this->ProcessSizeChanging(this->DrawingShape->Height, height, Y, 1, Field->SetTop);
}

inline void PrimitivePaint::MainPage::DeregisterTokens() {
	if (PointerPressedToken.Value)
		Field->PointerPressed -= PointerPressedToken;
	if (PointerMovedToken.Value)
		Field->PointerMoved -= PointerMovedToken;
	if (PointerReleasedToken.Value)
		Field->PointerReleased -= PointerReleasedToken;
}


void PrimitivePaint::MainPage::ColourFill_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	FillColor = dynamic_cast<SolidColorBrush^>(dynamic_cast<Windows::UI::Xaml::Shapes::Rectangle^>(dynamic_cast<ComboBoxItem^>(ColourFill->SelectedValue)->Content)->Fill)->Color;
}


void PrimitivePaint::MainPage::EraserButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	DeregisterTokens();

	PointerPressedToken = Field->PointerPressed += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnEraserPressed);
	PointerMovedToken = Field->PointerMoved += ref new Windows::UI::Xaml::Input::PointerEventHandler(this, &PrimitivePaint::MainPage::OnEraserMoved);
}


void PrimitivePaint::MainPage::OnEraserPressed(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	auto pline = ref new Polyline();
	pline->Points->Append(e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Position);
	pline->Stroke = ref new SolidColorBrush(Colors::White);
	pline->StrokeThickness = StrokeThickness;

	pline->StrokeMiterLimit = 0;

	this->DrawingShape = pline;
	Field->Children->Append(this->DrawingShape);
}


void PrimitivePaint::MainPage::OnEraserMoved(Platform::Object ^sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs ^e)
{
	if (!e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Properties->IsLeftButtonPressed) return;

	auto pline = dynamic_cast<Polyline^>(this->DrawingShape);
	pline->Points->Append(e->GetCurrentPoint(dynamic_cast<UIElement^>(sender))->Position);
}
