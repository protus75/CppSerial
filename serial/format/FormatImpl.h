#ifndef SERIAL_FORMAT_FORMATIMPL_H
#define SERIAL_FORMAT_FORMATIMPL_H

#include "Format.h"

namespace serial::format::in
{

	class Value : public serial::format::In
	{
	public: 
		Value() = default;

	protected:
		virtual void _Read(std::istream& arS, serial::tree::Elem& arElem) const;

	};

	class KeyEqValue : public serial::format::In
	{
	public:
		KeyEqValue() = default;

	protected:
		virtual void _Read(std::istream& arS, serial::tree::Elem& arElem) const;

	};

}

namespace serial::format::out
{
	class Value : public serial::format::Out
	{
	public:
		Value() = default;

	protected:

		virtual void _Write(std::ostream& arS, const serial::tree::Elem& aElem) const;

		virtual void _SeparatorKv(std::ostream& arS) const;

		virtual void _Separator(std::ostream& arS) const;
	};

	class KeyEqValue : public serial::format::Out
	{
	public:
		KeyEqValue() = default;

	protected:
		virtual void _Write(std::ostream& arS, const serial::tree::Elem& aElem) const;

		virtual void _SeparatorKv(std::ostream& arS) const;

		virtual void _Separator(std::ostream& arS) const;

	};

}

#endif