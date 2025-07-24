#include "mpiwrapper.h"
#include <iostream>

int main(int argc, char* argv[]) {
    mp_init(&argc, &argv);

    int world_size;
    mp_comm_size(&world_size);

    int world_rank;
    mp_comm_rank(&world_rank);

    if (world_rank == 0) {
        std::cout << "World size: " << world_size << std::endl;
    }

    mp_finalize();
    return 0;
}
