#ifndef MCLIB_COMMON_POSITION_H_
#define MCLIB_COMMON_POSITION_H_

#include <mclib/mclib.h>
#include <mclib/common/Types.h>
#include <mclib/protocol/ProtocolState.h>
#include <iosfwd>
#include <string>

namespace mc {

class DataBuffer;

class Position {
private:
    s64 m_X;
    s64 m_Y;
    s64 m_Z;
	mc::protocol::Version m_Version;

public:
    Position(mc::protocol::Version version) noexcept : m_X(0), m_Y(0), m_Z(0), m_Version(version) { }
    MCLIB_API Position(s32 x, s32 y, s32 z, mc::protocol::Version version) noexcept;
    s64 MCLIB_API Encode64() const noexcept;

    s64 GetX() const { return m_X; }
    s64 GetY() const { return m_Y; }
    s64 GetZ() const { return m_Z; }

    friend MCLIB_API DataBuffer& operator<<(DataBuffer& out, const Position& pos);
    friend MCLIB_API DataBuffer& operator>>(DataBuffer& in, Position& pos);
};

MCLIB_API DataBuffer& operator<<(DataBuffer& out, const Position& pos);
MCLIB_API DataBuffer& operator>>(DataBuffer& in, Position& pos);

MCLIB_API std::string to_string(const Position& data);

} // ns mc

MCLIB_API std::ostream& operator<<(std::ostream& out, const mc::Position& pos);
MCLIB_API std::wostream& operator<<(std::wostream& out, const mc::Position& pos);

#endif
