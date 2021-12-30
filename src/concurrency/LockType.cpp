#include "concurrency/LockType.h"

namespace LT {
    bool compatible(LockType a, LockType b) {
        switch (a) {
            case S:
                return b == IS || b == S || b == NL;
            case IS:
                return b != X;
            case IX:
                return b == IX || b == IS || b == NL;
            case SIX:
                return b == IS || b == NL;
            case X:
                return b == NL;
            case NL:
                return true;
        }
    }

    LockType parentLock(LockType lt) {
        switch (lt) {
            case S:
            case IS:
                return IS;
            case X:
            case IX:
            case SIX:
                return IX;
            case NL:
                return NL;
        }
    }

    bool canBeParentLock(LockType parent, LockType child) {
        switch (child) {
            case S:
            case IS:
                return parent == IS || parent == IX || parent == S || parent == SIX || parent == X;
            case IX:
            case SIX:
            case X:
                return parent == IX || parent == SIX || parent == X;
            case NL:
                return true;
        }
    }

    bool substitutable(LockType substitute, LockType require) {
        switch (require) {
            case NL:
                return true;
            case S:
                return substitute == S || substitute == X || substitute == SIX;
            case X:
                return substitute == X;
            case IS:
                return substitute == IS || substitute == X || substitute == IX || substitute == SIX;
            case IX:
                return substitute == X || substitute == SIX || substitute == IX;
            case SIX:
                return substitute == X || substitute == SIX;
        }
    }

}

std::ostream &operator<<(std::ostream &out, LockType lt) {
    switch (lt) {
        case S:
            out << "S";
            break;
        case X:
            out << "X";
            break;
        case IS:
            out << "IS";
            break;
        case IX:
            out << "IX";
            break;
        case SIX:
            out << "SIX";
            break;
        case NL:
            out << "NL";
            break;
    }
    return out;
}
