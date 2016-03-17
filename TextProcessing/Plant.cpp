#include "pch.h"

using namespace TextProcessing;

Plant::Plant(
	String^ _title,
	String^ _kingdom,
	String^ _divison,
	String^ _class,
	String^ _order,
	String^ _family,
	String^ _genus
)
{
	Title = _title;
	Kingdom = _kingdom;
	Division = _divison;
	Class = _class;
	Order = _order;
	Family = _family;
	Genus = _genus;
}

