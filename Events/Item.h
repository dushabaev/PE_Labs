#pragma once
using namespace Platform;
namespace Events {
	public ref class AdjustmentItem sealed
	{
	public:

		AdjustmentItem(String^ tile, float32 price, float32 count)
		{
			Title = tile;
			Price = price;
			Count = count;
		}
		property String^ Title;
		property float32 Price;
		property float32 Count;
	};
}