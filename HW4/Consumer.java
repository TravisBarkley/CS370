public class Consumer implements Runnable
{
    private int max = 1000000;

    private BoundedBuffer boundedBuffer; // buffer obj
    private int numItemsConsumed; // counter
    private double sum = 0; // sum of elements

    public Consumer(BoundedBuffer boundedBuffer)
    {
        this.boundedBuffer = boundedBuffer;
    }

    @Override
    public synchronized void run()
    {
        for(numItemsConsumed = 1; numItemsConsumed <= max; ++numItemsConsumed)
        {
            // consume
            double bufferElement = boundedBuffer.pop();
            sum += bufferElement;

            // print every 100000 items
            if(numItemsConsumed % 100000 == 0)
            {
                System.out.printf("Consumer: Consumed %d items, Cumulative value of consumed items=%.3f\n", numItemsConsumed, sum);
            }
        }

        System.out.println("Consumer: Finished consuming 1000000 items");
    }
}
