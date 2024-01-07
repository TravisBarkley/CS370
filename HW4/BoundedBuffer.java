public class BoundedBuffer
{
    private int maxElements = 1000; // buffer limit

    private double[] bufferElements = new double[maxElements]; // buffer
    private int popInd = 0; // index to remove from
    private int pushInd = -1; // index to add to
    private int size = 0; // elements in buffer

    // returns if buffer is full
    private boolean isFull()
    {
        if (size == maxElements) return true;
        return false;
    }

    // returns if the circular buffer is empty
    private boolean isEmpty()
    {
        if (size == 0) return true;
        return false;
    }

    // puts elements in buffer
    public synchronized void push(double bufferElement)
    {
        while(isFull()) //if full wait
        {
            try
            {
                wait();
            }
            catch(InterruptedException e)
            {
                e.printStackTrace();
            }
        }

        // insert and notify
        ++size;
        bufferElements[++pushInd % maxElements] = bufferElement;
        notify();
    }

    // removes element from buff
    public synchronized double pop()
    {
        while(isEmpty())//wait wehn empty
        {
            try
            {
                wait();
            }
            catch(InterruptedException e)
            {
                e.printStackTrace();
            }
        }

        // remove and notify
        --size;
        notify();
        return bufferElements[popInd++ % maxElements];
    }
}
