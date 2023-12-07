#ifndef SERIAL_FORMAT_FORMAT_H
#define SERIAL_FORMAT_FORMAT_H

#include <string>
#include <memory>

#include "../tree/ValueFwd.h"
#include "../tree/ElemFwd.h"
#include "../tree/PeersFwd.h"

#include "FormatFwd.h"

namespace serial::format
{
	typedef std::unique_ptr<In> InP;

	typedef std::unique_ptr<Out> OutP;

	struct Config
	{
		explicit Config(
			STRING::QUOTE::Quote aQuote,
			KEY::EXTRA::Extra aExtra,
			KEY::MISSING::Missing aMissing,
			ELEM::SPAN::Span aSpan,
			ROOT::TABLE::Table aTable
		);

		static Config Default();

		STRING::QUOTE::Quote Quote;
		KEY::EXTRA::Extra Extra;
		KEY::MISSING::Missing Missing;
		ELEM::SPAN::Span Span;
		ROOT::TABLE::Table Table;
	};
}

namespace serial::format
{
	class In
	{
	public:
		In() = default;

		virtual ~In() = default;

		In(const In&) = delete;

		In& operator=(const In&) = delete;

	public:
		static InP ReaderP(TYPE::Type aType);

	public:
		void Get(std::istream& arS, serial::tree::Elem& arElem) const;


		void Read(std::istream& arS, serial::tree::Peers& arKids) const;

		void Read(std::istream& arS, serial::tree::Elem& arChild) const;

		void ReadLen(std::istream& arS, serial::tree::ValueP& arLen) const;

		void ReadKey(std::istream& arS, serial::tree::ValueP& arLen) const;

	protected:
		virtual	void _Get(std::istream& arS, serial::tree::Elem& arElem) const;


		virtual void _Begin(std::istream& arS) const;

		virtual void _End(std::istream& arS) const;


		virtual void _Read(std::istream& arS, serial::tree::Peers& arKids) const;

		virtual void _Read(std::istream& arS, serial::tree::Elem& arChild) const = 0;

		virtual void _ReadLen(std::istream& arS, serial::tree::ValueP& arLenP) const;

		virtual void _ReadKey(std::istream& arS, serial::tree::ValueP& arKeyP) const;
	};
}

namespace serial::format
{
	class Out
	{
	public:
		Out() = default;

		virtual ~Out() = default;

		Out(const Out&) = delete;

		Out& operator=(const Out&) = delete;

	public:
		static OutP WriterP(TYPE::Type aType);

	public:
		void Put(std::ostream& arS, const serial::tree::Elem& aElem) const;


		void Write(std::ostream& arS, const serial::tree::Peers& aKids) const;

		void Write(std::ostream& arS, const serial::tree::Elem& aChild) const;

		void WriteLen(std::ostream& arS, const serial::tree::ValueP& aLenP) const;

		void WriteKey(std::ostream& arS, const serial::tree::ValueP& aLenP) const;

	protected:

		virtual void _Put(std::ostream& arS, const serial::tree::Elem& aElem) const;

		
		virtual void _SeparatorKv(std::ostream& arS) const;

		virtual void _Separator(std::ostream& arS) const;

		virtual void _Begin(std::ostream& arS) const;

		virtual void _End(std::ostream& arS) const;


		virtual void _Write(std::ostream& arS, const serial::tree::Peers& aKids) const;

		virtual void _Write(std::ostream& arS, const serial::tree::Elem& aChild) const = 0;

		virtual void _WriteLen(std::ostream& arS, const serial::tree::ValueP& aLenP) const;

		virtual void _WriteKey(std::ostream& arS, const serial::tree::ValueP& aLenP) const;
	};
}

#endif