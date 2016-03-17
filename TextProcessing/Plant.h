#pragma once
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace TextProcessing {
	public ref class Plant sealed
	{
	public:
		Plant(
			String^ _title,
			String^ _kingdom,
			String^ _divison,
			String^ _class,
			String^ _order,
			String^ _family,
			String^ _genus
			);
		property String^ Title;

		property String^ Kingdom;
		property String^ Division;
		property String^ Class;
		property String^ Order;
		property String^ Family;
		property String^ Genus;
	};
}