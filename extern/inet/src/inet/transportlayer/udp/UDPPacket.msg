//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//


cplusplus {{
#include "inet/common/INETDefs.h"
}}

namespace inet;

enum UdpConstants{
    UDP_HEADER_BYTES = 8;
};
//
// Represents an UDP packet, to be used with the ~UDP module.
//
packet UDPPacket
{
    @customize(true);
    @fieldNameSuffix("_var"); //TODO remove when OMNeT++ 4.x compatibility is no longer required

    unsigned short srcPort;
    unsigned short destPort;
    byteLength = UDP_HEADER_BYTES;
    int totalLengthField = -1;   // -1 means: getTotalLengthField() uses getByteLength()
}

