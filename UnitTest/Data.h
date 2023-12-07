#ifndef DATA_H
#define DATA_H

#include "../Serial/tree/ValueImpl.h"
#include "../Serial/tree/KeyImpl.h"
#include "../Serial/tree/ElemImpl.h"
#include "../Serial/tree/PeersImpl.h"

namespace data
{
	namespace Value
	{
		struct UserNative
		{
			int mI = int();
			bool mB = bool();
			std::string mS = std::string();

			void Children(serial::tree::Peers& arChildren)
			{
				serial::tree::Node("int", mI, arChildren);
				serial::tree::Node("bool", mB, arChildren);
				serial::tree::Node("string", mS, arChildren);
			}
		};

		struct UserUser
		{
			UserNative mU = UserNative();

			void Children(serial::tree::Peers& arChildren)
			{
				serial::tree::Node("user", mU, arChildren);
			}
		};

		struct UserVector
		{
			std::vector<int> mIs = std::vector<int>{ 1, 2, 3 };

			void Children(serial::tree::Peers& arChildren)
			{
				serial::tree::Node("ints", mIs, arChildren);
			}
		};

		struct UserVectorVector
		{
			std::vector<std::vector<int>> mIIs = std::vector<std::vector<int>>{ { 1, 2, 3 } };

			void Children(serial::tree::Peers& arChildren)
			{
				serial::tree::Node("ints", mIIs, arChildren);
			}
		};

		struct UserPair
		{
			std::pair<int, std::string> mP = std::pair<int, std::string>(1, "abc");

			void Children(serial::tree::Peers& arChildren)
			{
				serial::tree::Node("mP", mP, arChildren);
			}
		};

		struct UserPairPair
		{
			std::pair<int, std::pair<std::string, bool>> mPP 
				= std::pair<int, std::pair<std::string, bool>>(1, std::pair<std::string, bool>("abc", true));

			void Children(serial::tree::Peers& arChildren)
			{
				serial::tree::Node("mPP", mPP, arChildren);
			}
		};

		struct UserSet
		{
			std::set<int> mS{ 1, 2, 3 };

			void Children(serial::tree::Peers& arChildren)
			{
				serial::tree::Node("mS", mS, arChildren);
			}
		};

		struct UserDict
		{
			std::map<int, std::string> mD{{1, "abc"}};

			void Children(serial::tree::Peers& arChildren)
			{
				serial::tree::Node("mD", mD, arChildren);
			}
		};

		struct UserDictDict
		{
			std::map<int, std::map<std::string, bool>> mDD{{1, {{ "abc", true}}}};

			void Children(serial::tree::Peers& arChildren)
			{
				serial::tree::Node("mDD", mDD, arChildren);
			}
		};

	}
}

namespace data
{
	class Member
	{
		int m;

	public:
		int M() const;

		/// <summary>
		/// Add a _public_ member function of this signature
		/// </summary>
		void Children(serial::tree::Peers& arChildren);
	};
}
namespace data
{
	inline int Member::M() const
	{
		return m;
	}

	inline void Member::Children(serial::tree::Peers& arChildren)
	{
		serial::tree::Node("int", m, arChildren);
	}
}

namespace data
{
	/// <summary>
	/// Inherit from the interface class
	/// </summary>
	class Inherit : public serial::tree::Connect
	{
		int m;

	public:
		int M() const;

	protected:
		/// <summary>
		/// Add this member function, can choose scope
		/// </summary>
		virtual void _Children(serial::tree::Peers& arChildren);
	};
}

namespace data
{
	inline int Inherit::M() const
	{
		return m;
	}

	inline void Inherit::_Children(serial::tree::Peers& arChildren)
	{
		serial::tree::Node("int", m, arChildren);
	}
}

namespace data
{
	struct Free
	{
		int m;
	};
}

namespace serial::tree
{
	/// <summary>
	/// Specialize this template function with a data type that has open members
	/// </summary>
	template <>
	void Children<data::Free>(data::Free& arT, tree::Peers& arChildren);
}
namespace serial::tree
{
	template <>
	inline void Children<data::Free>(data::Free& arT, tree::Peers& arChildren)
	{
		serial::tree::Node("int", arT.m, arChildren);
	}
}

#endif