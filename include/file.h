#pragma once

#include "types.h"

namespace dmg {

class shared_file_descriptor;

shared_file_descriptor open_anonymous_file(size_type, int);

}