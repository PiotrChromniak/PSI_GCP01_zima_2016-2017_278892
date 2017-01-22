using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using AForge;
using AForge.Neuro;
using AForge.Neuro.Learning;
using System.Diagnostics;

namespace WTA
{
    class Program
    {
        private double[][] input, validateInput;
        double[][] output;
        private double learningRate = 0.1;
        private DistanceNetwork network;
        private ActivationNetwork aNetwork;
        private StreamWriter fileOutput = new StreamWriter(@"C:\Users\Viator\Documents\Visual Studio 2015\Projects\WTA\WTA\log.txt");

        public void loadInput(string fileName, string validateFileName)
        {
            try
            {
                using (StreamReader sr = new StreamReader(fileName))
                {
                    string[] temp = sr.ReadLine().Split(' ');
                    int rows = int.Parse(temp[0]), columns = int.Parse(temp[1]);

                    input = new double[rows][];
                    for (int i = 0; i < rows; ++i)
                        input[i] = new double[columns];
                    
                    for (int i = 0; i < rows; ++i)
                    {
                        string[] row = sr.ReadLine().Split(' ');
                        for (int j = 0; j < columns; ++j)
                            input[i][j] = double.Parse(row[j]);
                    }
                }


            }
            catch (Exception ex)
            {
                Console.WriteLine("Error while reading file from " + fileName);
            }

            try
            {
                using (StreamReader sr1 = new StreamReader(validateFileName))
                {
                    string[] temp1 = sr1.ReadLine().Split(' ');
                    int rows = int.Parse(temp1[0]), columns = int.Parse(temp1[1]);
                    validateInput = new double[rows][];
                    for (int i = 0; i < rows; ++i)
                        validateInput[i] = new double[columns];

                    for (int i = 0; i < rows; ++i)
                    {
                        string[] row = sr1.ReadLine().Split(' ');
                        for (int j = 0; j < columns; ++j)
                            validateInput[i][j] = double.Parse(row[j]);
                    }
                }
            }
            catch(Exception ex)
            {
                Console.WriteLine("Error while reading file from " + fileName);
            }
        }

        public void WtaLearning(int epochs, int reportInterval)
        {
            network = new DistanceNetwork(20, 9);
            SOMLearning trainer = new SOMLearning(network);
            learningRate = 0.1;
            double fixedLearningRate = learningRate / 10;
            double driftingLearningRate = fixedLearningRate * 9;

            int i = 0;

            trainer.LearningRadius = 0.0;

            while (i< epochs)
            {
                trainer.LearningRate = driftingLearningRate * (epochs - i) / epochs + fixedLearningRate;
                //int iterations = 0;
                //double ERR = 0.0;
                //while (iterations < input.Length)
                //{
                //    trainer.LearningRadius = 0.0;
                //    trainer.LearningRate = driftingLearningRate * (iterations - i) / iterations + fixedLearningRate;
                //    ERR += trainer.Run(input[iterations]);
                //    ++iterations;
                //    Console.WriteLine("WINNER: " + network.GetWinner());
                //}
                //Console.WriteLine("ITER " + iterations + " ERR " + ERR);
                double err = trainer.RunEpoch(input);
                fileOutput.WriteLine(err);
                if (i % reportInterval==0)
                {
                    Console.WriteLine("Epoch " + (i + 1) + " Error " + err);
                }
                ++i;
            }
        }

        public void WtaTest()
        {
            double[] outpt;
            for (int i = 0; i < validateInput.Length; ++i)
                outpt = network.Compute(validateInput[i]);
        }


        public void loadInputOutput(string fileName)
        {
            try
            {
                using (StreamReader sr = new StreamReader(fileName))
                {
                    string[] temp = sr.ReadLine().Split(' ');
                    int rows = int.Parse(temp[0]), columns = int.Parse(temp[1]);

                    input = new double[rows][];
                    output = new double[rows][];
                    for (int i = 0; i < rows; ++i)
                    {
                        input[i] = new double[columns];
                        output[i] = new double[1];
                    }

                    for (int i = 0; i < rows; ++i)
                    {
                        string[] row = sr.ReadLine().Split(' ');
                        string tempOut = sr.ReadLine();
                        output[i][0] = Double.Parse(tempOut);
                        for (int j = 0; j < columns; ++j)
                            input[i][j] = double.Parse(row[j]);
                    }
                }


            }
            catch (Exception ex)
            {
                Console.WriteLine("Error while reading file from " + fileName);
            }
        }

        public void learnBackprop(int epochs, int reportInterval)
        {
            aNetwork = new ActivationNetwork(new SigmoidFunction(), 20, 1);
            BackPropagationLearning trainer = new BackPropagationLearning(aNetwork);
            trainer.LearningRate = 0.01;
            for(int i = 0;i< epochs; ++i){
                double error = trainer.RunEpoch(input, output);
                if(i%reportInterval == 0)
                {
                    Console.WriteLine("Error " + error);
                }
            }
        }

        static void Main(string[] args)
        {
            StreamWriter timeFile = new StreamWriter(@"C:\Users\Viator\Documents\Visual Studio 2015\Projects\WTA\WTA\time_log.txt");

            Program p = new Program();
            p.loadInput(@"C:\Users\Viator\Documents\Visual Studio 2015\Projects\WTA\WTA\unsupervised.txt", @"C:\Users\Viator\Documents\Visual Studio 2015\Projects\WTA\WTA\unsupervised validation.txt");
            Stopwatch sw = new Stopwatch();

            sw.Start();
            p.WtaLearning(250, 10);
            sw.Stop();

            long microseconds = sw.ElapsedTicks / (Stopwatch.Frequency / (1000L * 1000L));
            timeFile.WriteLine(sw.Elapsed.Milliseconds);
            Console.WriteLine("Elapsed={0}", microseconds);
            p.WtaTest();


            //Program p = new Program();
            //p.loadInputOutput(@"C:\Users\Viator\Documents\Visual Studio 2015\Projects\WTA\WTA\backprop.txt");
            //p.learnBackprop(250, 1);
        }
        }
    }