#include "FormatImpl.h"

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "../tree/Key.h"
#include "../tree/Value.h"
#include "../tree/Elem.h"
#include "../tree/PeersImpl.h"

namespace serial::format
{
	Config::Config(
		STRING::QUOTE::Quote aQuote,
		KEY::EXTRA::Extra aExtra,
		KEY::MISSING::Missing aMissing,
		ELEM::SPAN::Span aSpan,
		ROOT::TABLE::Table aTable
	)
		: Quote(aQuote)
		, Extra(aExtra)
		, Missing(aMissing)
		, Span(aSpan)
		, Table(aTable)
	{
	}

	Config Config::Default()
	{
		return Config(
			STRING::QUOTE::DEFAULT,
			KEY::EXTRA::DEFAULT,
			KEY::MISSING::DEFAULT,
			ELEM::SPAN::DEFAULT,
			ROOT::TABLE::DEFAULT
		);
	}
}

namespace serial::format
{
	bool IsLeftover(std::istream& arS)
	{
		std::string s;
		arS >> s;

		return not arS.fail();
	}

	void TestLeftover(std::istream& arS)
	{
		if (IsLeftover(arS))
		{
			throw std::runtime_error("unread leftovers in stream");
		}
	}
}

namespace serial::format
{

	InP In::ReaderP(TYPE::Type aType)
	{
		switch (aType)
		{
		case TYPE::VALUE:
		{
			return InP(new in::Value());
		}
		case TYPE::KEY_EQ_VALUE:
		{
			return InP(new in::KeyEqValue());
		}
		}

		InP p;
		return p;
	}

	void In::Read(std::istream& arS, serial::tree::Elem& arElem) const
	{
		_Read(arS, arElem);
	}

	void In::_Read(std::istream& arS, serial::tree::Peers& arKids) const
	{
		for (auto it = arKids.mItems.begin(); it != arKids.mItems.end(); ++it)
		{
			_Read(arS, *it);
		}
	}

	void In::Read(std::istream& arS, serial::tree::Peers& arKids) const
	{
		_Read(arS, arKids);
	}

	void In::_Begin(std::istream& arS) const
	{
	}

	void In::_End(std::istream& arS) const
	{
	}

	void In::_Get(std::istream& arS, serial::tree::Elem& arElem) const
	{
		_Begin(arS);
		_Read(arS, arElem);
		_End(arS);
	}

	void In::Get(std::istream& arS, serial::tree::Elem& arElem) const
	{
		_Get(arS, arElem);
	}

	void In::_ReadLen(std::istream& arS, serial::tree::ValueP& arLenP) const
	{
		arLenP->Get(*this, arS);
	}

	void In::ReadLen(std::istream& arS, serial::tree::ValueP& arLenP) const
	{
		_ReadLen(arS, arLenP);
	}

	void In::_ReadKey(std::istream& arS, serial::tree::ValueP& arLenP) const
	{
		arLenP->Get(*this, arS);
	}

	void In::ReadKey(std::istream& arS, serial::tree::ValueP& arLenP) const
	{
		_ReadKey(arS, arLenP);
	}
}

namespace serial::format::in
{
	void Value::_Read(std::istream& arS, serial::tree::Elem& arElem) const
	{
		arElem.mValueP->Get(*this, arS);
	}
}

namespace serial::format::in
{
	void KeyEqValue::_Read(std::istream& arS, serial::tree::Elem& arElem) const
	{
		if (arElem.IsParent())
		{
			arElem.mValueP->Get(*this, arS);
		}
		else
		{
			std::string kv;
			arS >> kv;

			auto key = std::string("");

			if (arS)
			{
				std::stringstream tmp(kv);
				std::getline(tmp, key, '=');

				arElem.mValueP->Get(*this, tmp);
			}

			if (arS)
			{
				if (key != arElem.mKey.mrT)
				{
					throw std::runtime_error("key mismatch");
				}
			}
		}
	}
}

namespace serial::format
{
	OutP Out::WriterP(TYPE::Type aType)
	{
		switch (aType)
		{
		case TYPE::VALUE:
		{
			return OutP(new out::Value());
		}
		case TYPE::KEY_EQ_VALUE:
		{
			return OutP(new out::KeyEqValue());
		}
		}

		OutP p;
		return p;
	}

	void Out::Write(std::ostream& arS, const serial::tree::Elem& aElem) const
	{
		_Write(arS, aElem);
	}

	void Out::_SeparatorKv(std::ostream& arS) const
	{
	}

	void Out::_Separator(std::ostream& arS) const
	{
	}

	void Out::_Begin(std::ostream& arS) const
	{
	}

	void Out::_End(std::ostream& arS) const
	{
	}

	void Out::_Put(std::ostream& arS, const serial::tree::Elem& aElem) const
	{
		_Begin(arS);
		_Write(arS, aElem);
		_End(arS);
	}

	void Out::Put(std::ostream& arS, const serial::tree::Elem& aElem) const
	{
		_Put(arS, aElem);
	}

	void Out::_Write(std::ostream& arS, const serial::tree::Peers& aKids) const
	{
		auto it = aKids.mItems.begin();
		
		if (it != aKids.mItems.end())
		{
			_Write(arS, *it);
			++it;
		}

		for (; it != aKids.mItems.end(); ++it)
		{
			_Separator(arS);
			_Write(arS, *it);
		}
	}

	void Out::Write(std::ostream& arS, const serial::tree::Peers& aKids) const
	{
		_Write(arS, aKids);
	}

	void Out::_WriteLen(std::ostream& arS, const serial::tree::ValueP& aLenP) const
	{
		aLenP->Put(*this, arS);
	}

	void Out::WriteLen(std::ostream& arS, const serial::tree::ValueP& aLenP) const
	{
		_WriteLen(arS, aLenP);
		_Separator(arS);
	}

	void Out::_WriteKey(std::ostream& arS, const serial::tree::ValueP& aLenP) const
	{
		aLenP->Put(*this, arS);
	}

	void Out::WriteKey(std::ostream& arS, const serial::tree::ValueP& aLenP) const
	{
		_WriteKey(arS, aLenP);
		_SeparatorKv(arS);
	}

}

namespace serial::format::out
{
	void Value::_Write(std::ostream& arS, const serial::tree::Elem& aElem) const
	{
		aElem.mValueP->Put(*this, arS);
	}

	void Value::_SeparatorKv(std::ostream& arS) const
	{
		arS << " ";
	}

	void Value::_Separator(std::ostream& arS) const
	{
		arS << " ";
	}
}

namespace serial::format::out
{
	void KeyEqValue::_Write(std::ostream& arS, const serial::tree::Elem& aElem) const
	{
		if (aElem.IsChildless())
		{
			aElem.mKey.Put(*this, arS);
			arS << '=';
		}

		aElem.mValueP->Put(*this, arS);
	}

	void KeyEqValue::_Separator(std::ostream& arS) const
	{
		arS << " ";
	}

	void KeyEqValue::_SeparatorKv(std::ostream& arS) const
	{
		arS << " ";
	}

}