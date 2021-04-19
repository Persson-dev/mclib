#pragma once

#include <mclib/block/Block.h>

//currently only works for 1.16 and 1.15

namespace mc{
	namespace inventory{

		class ItemRegistry;

		class Item{
		public:
			const std::string& getName() const{
				return m_Name;
			}
			u32 getID() const{
				return m_Data;
			}
			//block corresponding to the item, nullptr if none
			block::BlockPtr getBlock() const{
				return m_Block;
			}
			Item(const std::string& name, u32 data) : m_Name(name), m_Data(data), m_Block(nullptr){}
			//TODO mapping item to its corresponding block 
			void setBlock(block::BlockPtr block);
		private:
			std::string m_Name;
			u32 m_Data;
			block::BlockPtr m_Block;

			friend class ItemRegistry;
		};

		typedef Item* ItemPtr;

		class ItemRegistry{
		private:
			std::unordered_map<u32, ItemPtr> m_Items;
			std::unordered_map<std::string, ItemPtr> m_ItemNames;

			ItemRegistry(){}
		public:
			static MCLIB_API ItemRegistry* GetInstance();

			MCLIB_API ~ItemRegistry();

			ItemPtr GetItem(u32 data) const{
				auto iter = m_Items.find(data);

				if (iter == m_Items.end()){
					data &= ~15; // Return basic version if the meta type can't be found
					iter = m_Items.find(data);
					if (iter == m_Items.end())
						return nullptr;
				}
				return iter->second;
			}

			ItemPtr MCLIB_API GetItem(const std::string& name) const{
				auto iter = m_ItemNames.find(name);
				if (iter == m_ItemNames.end()) return nullptr;
				return iter->second;
			}

			ItemPtr GetItem(u16 type, u16 meta) const{
				u16 data = (type << 4) | (meta & 15);
				return GetItem(data);
			}

			void RegisterItem(ItemPtr item){
				m_Items[item->getID()] = item;
				m_ItemNames[item->getName()] = item;
			}

			void MCLIB_API RegisterVanillaItems(protocol::Version protocolVersion);
			void MCLIB_API ClearRegistry();
		};

	}
}