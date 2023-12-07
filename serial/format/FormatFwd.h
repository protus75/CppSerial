#ifndef SERIAL_FORMAT_FORMATFWD_H
#define SERIAL_FORMAT_FORMATFWD_H

namespace serial::format
{
	class In;
	class Out;


	namespace STRING
	{
		namespace QUOTE
		{
			enum Quote
			{
				QUOTED,
				UNQUOTED,
				DEFAULT = UNQUOTED
			};
		}
	}

	namespace KEY
	{
		namespace MISSING
		{
			enum Missing
			{
				OK,
				ERROR,
				DEFAULT = OK
			};
		}

		namespace EXTRA
		{
			enum Extra
			{
				OK,
				ERROR,
				DEFAULT = ERROR
			};
		}
	}

	namespace ELEM
	{
		namespace SPAN
		{
			enum Span
			{
				WHOLE_LINE,
				FREE_FORM,
				DEFAULT = WHOLE_LINE
			};
		}
	}

	namespace ROOT
	{
		namespace TABLE
		{
			enum Table
			{
				ANONYMOUS,
				NAMED,
				DEFAULT = ANONYMOUS
			};
		}
	}

	namespace WRITE
	{
		namespace VALID
		{
			enum Valid
			{
				ONLY,
				ALWAYS
			};
		}

		namespace SEPARATOR
		{
			enum Separator
			{
				ALWAYS,
				NEVER
			};
		}
	}

	namespace TYPE
	{
		enum Type
		{
			VALUE, /// space separated values (NO keys)
			QUOTED, /// like TEXT but with quotes on string values
			COMMA, /// like TEXT but with commas in between values
			COLON, /// like TEXT but with colon in between values
			KEY_EQ_VALUE, 
			URL_QUERY
		};
	}
}

#endif