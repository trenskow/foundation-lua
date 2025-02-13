//
// type.hpp
// foundation-lua
//
// Created by Kristian Trenskow on 2023/11/09
// See license in LICENSE.
//

#ifndef foundation_lua_type_hpp
#define foundation_lua_type_hpp

#include "../foundation/src/foundation.hpp"

#include "../state.hpp"

namespace foundation::lua::types {

	class LuaBoolean;
	class LuaNumber;
	class LuaString;
	class LuaFunction;
	class LuaTable;
	class Caller;
	class LuaUserFunction;
	class LuaValue;
	class LuaLightUserData;

	class LuaType : public Object {

		friend class Strong<LuaType>;
		friend class foundation::lua::State;
		friend class Caller;
		friend class LuaTable;
		friend class LuaUserFunction;
		friend class LuaValue;

		public:

			enum class Kind : uint8_t {
				nil = 0,
				boolean,
				number,
				string,
				function,
				table,
				lightUserData
			};

			LuaType(const LuaType&) = delete;
			virtual ~LuaType();

			inline State& state() const {
				return this->_state;
			}

			virtual Kind kind() const;
			virtual String kindDescription() const;

			Strong<Type> foundation(
				bool trueNull = true
			) const noexcept(false);

			Strong<LuaBoolean> boolean() const noexcept(false);
			Strong<LuaNumber> number() const noexcept(false);
			Strong<LuaString> string() const noexcept(false);
			Strong<LuaFunction> function() const noexcept(false);
			Strong<LuaTable> table() const noexcept(false);
			Strong<LuaLightUserData> lightUserData() const noexcept(false);

			bool operator==(
				nullptr_t
			) const;

			bool operator!=(
				nullptr_t
			) const;

		protected:

			LuaType(
				State& state);

			ssize_t stackIndex() const;

			ssize_t stackIndexOf(
				size_t stackOffset
			) const;

			virtual Strong<LuaType> underlying() const;

			Strong<LuaType> push() const;

			Strong<LuaType> replaced();

			bool rawEquals(
				const LuaType& other);

		private:

			Strong<Type> _foundation(
				bool trueNull,
				Array<Pair<LuaType, Type>>& crossReferences
			) const noexcept(false);

			static Strong<LuaType> _pick(
				State& state,
				ssize_t offset = 0);

			static Strong<Array<LuaType>> _pickUnclaimed(
				State& state);

			Strong<State> _state;
			size_t _stackOffset;

	};

}

#endif /* foundation_lua_type_hpp */
