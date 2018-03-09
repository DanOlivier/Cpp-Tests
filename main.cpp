#include "Queue.h"
#include "Consumer.h"
#include "Producer.h"

int main(void)
{
    Queue q;

    Consumer cons(q);
    Producer prod(q);

    cons.execute();
    prod.execute();

    prod.join();

    cons.stop();
    q.stop();

    cons.join();

    std::cout << "END" << std::endl;

    return EXIT_SUCCESS;
}
