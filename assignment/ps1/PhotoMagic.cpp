#include "FibLFSR.hpp"

namespace PhotoMagic {

std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr) {
    os << lfsr.getSeedBinaryString();

    return os;
}

}  // namespace PhotoMagic
