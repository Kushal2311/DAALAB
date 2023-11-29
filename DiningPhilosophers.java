import java.util.concurrent.Semaphore;

class Philosopher extends Thread {
    private int index;
    private Semaphore left_spoon;
    private Semaphore right_spoon;

    public Philosopher(int index, Semaphore left_spoon, Semaphore right_spoon) {
        this.index = index;
        this.left_spoon = left_spoon;
        this.right_spoon = right_spoon;
    }
// Declare two Functions Think() and Eat()

    private void think() throws InterruptedException {
        System.out.println("Philosopher " + index + " is thinking.");
        Thread.sleep((long) (Math.random() * 1000));
    }

    private void eat() throws InterruptedException {
        System.out.println("Philosopher " + index + " is trying to pick up chopsticks.");
        left_spoon.acquire();
        try {
            right_spoon.acquire();
            try {
                System.out.println("Philosopher " + index + " is eating.");
                Thread.sleep((long) (Math.random() * 1000));
            }
            finally {
                right_spoon.release();
            }
        }
        finally {
            left_spoon.release();
        }
        System.out.println("Philosopher " + index + " has finished a meal.");
    }

    @Override
    public void run() {
        try {
            while (true) {
                think();
                eat();
            }
        }
        catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

public class DiningPhilosophers {
    public static void main(String[] args) {
        int num = 5;
        Philosopher[] philosophers = new Philosopher[num];
        Semaphore[] spoon = new Semaphore[num];

        for (int i = 0; i < num; i++) {
            spoon [i] = new Semaphore(1);
        }

        for (int i = 0; i < num; i++) {
            // Array of Philosopher object Threads with respective index, left spoon and Right spoon
            philosophers[i] = new Philosopher(i, spoon[i], spoon[(i + 1) % num]);
            // Each Philosopher Thread object initialization
            philosophers[i].start();
            System.out.println("Thread " + i + " Started!");
        }

        // Run the simulation for a while
        try {
            Thread.sleep(10000); // Run for 10 seconds
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Stop the philosophers
        for (Philosopher i : philosophers) {
            i.interrupt();
        }
    }
}
