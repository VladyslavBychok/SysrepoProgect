#include "GeneratePath.hpp"

std::string GeneratePath::getPath(std::string number, VariantsPath path)
{
    switch (path)
    {
    case Name:
        _path = _pathName;
        _path.replace(53, 3, number);
        break;

    case IncomingNumber:
        _path = _pathIncomingNumber;
        _path.replace(53, 3, number);
        break;

    case State:
        _path = _pathState;
        _path.replace(53, 3, number);
        break;

    case Number:
        _path = _pathNumber;
        _path.replace(53, 3, number);
        break;

    case Subscriber:
        _path = _subscriber;
        _path.replace(53, 3, number);
        break;
    }

    return _path;
}