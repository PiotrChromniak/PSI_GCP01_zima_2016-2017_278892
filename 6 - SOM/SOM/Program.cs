using System;
using AForge.Neuro;
using System.IO;
using AForge.Neuro.Learning;
using System.Diagnostics;

namespace SOM
{
    class Program
    {
        private double[][] input;
        private DistanceNetwork network;

        public void loadDataFromFile(string fileName)
        {
            StreamReader sr = new StreamReader(fileName);
            String[] temp = sr.ReadLine().Split(' ');
            int rows = int.Parse(temp[0]), columns = int.Parse(temp[1]);

            input = new double[rows][];
            for (int i = 0; i < rows; ++i)
                input[i] = new double[columns];

            for(int i = 0; i < rows; ++i)
            {
                String[] tmp = sr.ReadLine().Split(' ');
                for(int j = 0; j < columns; ++j)
                {
                    input[i][j] = double.Parse(tmp[j]);
                }
            }

            network = new DistanceNetwork(24,10*10);
        }

        public void learningProcess(int epochs, int reportInterval)
        {
            SOMLearning trainer = new SOMLearning(network);
            double learningRate = 0.1;
            double radius = 10;
            double fixedLearningRate = learningRate / 10;
            double driftingLearningRate = fixedLearningRate * 9;

            StreamWriter errorLog = new StreamWriter(@"C:\Users\Viator\Documents\Visual Studio 2015\Projects\SOM\SOM\errorLog.txt"),
                winnerLog = new StreamWriter(@"C:\Users\Viator\Documents\Visual Studio 2015\Projects\SOM\SOM\winnerLog.txt");
            int epoch = 0;
            while (epoch < epochs)
            {
                trainer.LearningRate = driftingLearningRate * (epochs - epoch) / epochs + fixedLearningRate;
                trainer.LearningRadius = (double)radius * (epochs - epoch) / epochs;
                double error = 0.0;

                for(int iteration = 0;iteration < input.Length; ++iteration)
                {
                    error += trainer.Run(input[iteration]);
                    int winner = network.GetWinner();
                    char ascii = Convert.ToChar(iteration + 65);
                    winnerLog.WriteLine("{0} {1}", ascii, winner);


                    if (epoch % reportInterval == 0)
                    {

                        Console.WriteLine("{0} winner {1}", ascii, winner);
                    }
                }

                if (epoch % reportInterval == 0)
                {
                    Console.WriteLine("Epoch " + epoch + " error " + error);
                }
                errorLog.WriteLine(error);

                ++epoch;
            }

            errorLog.Close();
            winnerLog.Close();

        }

        static void Main(string[] args)
        {
            StreamWriter sw = new StreamWriter(@"C:\Users\Viator\Documents\Visual Studio 2015\Projects\SOM\SOM\time.txt");
            Stopwatch s = new Stopwatch();
            

            Program p = new Program();
            p.loadDataFromFile(@"C:\Users\Viator\Documents\Visual Studio 2015\Projects\SOM\SOM\data.txt");
            s.Start();
            p.learningProcess(20000, 19999);
            s.Stop();
                
            sw.WriteLine(s.ElapsedMilliseconds);
            sw.Close();

        }
    }
}
