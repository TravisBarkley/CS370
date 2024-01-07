import java.util.Random;

public class Producer implements Runnable
{
    private static final int max = 1000000;

    private BoundedBuffer boundedBuffer; // buffer obj
    private int numItemsGenerated; // counter
    private double sum = 0; // sum values

    public Producer(BoundedBuffer boundedBuffer)
    {
        this.boundedBuffer = boundedBuffer;
    }

    @Override
    public void run()
    {
        for(numItemsGenerated = 1; numItemsGenerated <= max; ++numItemsGenerated)
        {
            // gen rand and insert
            Random random = new Random();
            Double bufferElement = random.nextDouble() * 100.0;
            boundedBuffer.push(bufferElement);
            sum += bufferElement;

            // prints values every 100k
            if(numItemsGenerated % 100000 == 0)
            {
                System.out.printf("Producer: Generated %d items, Cumulative value of generated items=%.3f\n", numItemsGenerated, sum);
            }
        }

        System.out.println("Producer: Finished generating 1000000 items");
    }
}


