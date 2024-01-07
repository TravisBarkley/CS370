public class ProducerConsumer
{
    public static void main(String[] args)
    {
        BoundedBuffer boundedBuffer = new BoundedBuffer();
        Thread producer = new Thread(new Producer(boundedBuffer));
        Thread consumer = new Thread(new Consumer(boundedBuffer));

        // start
        producer.start();
        consumer.start();

        // waiting for the threads to join then leave
        try
        {
            producer.join();
            consumer.join();
        }
        catch(InterruptedException e)
        {
            e.printStackTrace();
        }

        System.out.println("Exiting!");
    }
}
