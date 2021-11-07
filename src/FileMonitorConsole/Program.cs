﻿using System;
using EaseFilter.FilterControl;

namespace FileMonitorConsole
{
    class Program
    {
        static FilterControl filterControl = new FilterControl();

        static void Main(string[] args)
        {
            string lastError = string.Empty;
            string licenseKey = "Email us to request a trial key: info@easefilter.com";
            
            FilterAPI.FilterType filterType = FilterAPI.FilterType.MONITOR_FILTER;
            int serviceThreads = 5;
            int connectionTimeOut = 10; //seconds

            try
            {
                //copy the right Dlls to the current folder.
                Utils.CopyOSPlatformDependentFiles(ref lastError);

                if (!filterControl.StartFilter(filterType, serviceThreads, connectionTimeOut, licenseKey, ref lastError))
                {
                    Console.WriteLine("Start Filter Service failed with error:" + lastError);
                    return;
                }

                //the watch path can use wildcard to be the file path filter mask.i.e. '*.txt' only monitor text file.
                string watchPath = "c:\\test\\*";

                if (args.Length > 0)
                {
                    watchPath = args[0];
                }

                //create a file monitor filter rule, every filter rule must have the unique watch path. 
                FileFilter fileMonitorFilter = new FileFilter(watchPath);

                //Filter the file change event to monitor all file change events.
                fileMonitorFilter.FileChangeEventFilter = (FilterAPI.MonitorFileEvents)FilterAPI.NotifyAllFileEvents;

                //register the file change callback events.
                fileMonitorFilter.NotifyFileWasChanged += NotifyFileChanged;

                //Filter the monitor file IO events
                fileMonitorFilter.MonitorFileIOEventFilter = (ulong)(MonitorFileIOEvents.OnFileOpen | MonitorFileIOEvents.OnFileRead);

                fileMonitorFilter.OnFileOpen += OnFileOpen;
                fileMonitorFilter.OnFileRead += OnFileRead;

                filterControl.AddFilter(fileMonitorFilter);

                if (!filterControl.SendConfigSettingsToFilter(ref lastError))
                {
                    Console.WriteLine("SendConfigSettingsToFilter failed." + lastError);
                    return;
                }

                Console.WriteLine("Start filter service succeeded.");

                // Wait for the user to quit the program.
                Console.WriteLine("Press 'q' to quit the sample.");
                while (Console.Read() != 'q') ;

                filterControl.StopFilter();

            }
            catch (Exception ex)
            {
                Console.WriteLine("Start filter service failed with error:" + ex.Message);
            }

        }

        /// <summary>
        /// Fires this event when the file was changed.
        /// </summary>
        static void NotifyFileChanged(object sender, FileChangeEventArgs e)
        {
            Console.WriteLine("NotifyFileChanged:" + e.FileName + ",eventType:" + e.eventType.ToString() + ",userName:" + e.UserName + ",processName:" + e.ProcessName);
        }

        /// <summary>
        /// Fires this event after the file was opened, the handle is not closed. 
        /// </summary>
        static void OnFileOpen(object sender, FileCreateEventArgs e)
        {
            Console.WriteLine("FileOpen:" + e.FileName + ",status:" +  e.IOStatusToString() + ",userName:" + e.UserName + ",processName:" + e.ProcessName);
        }

        /// <summary>
        /// Fires this event after the read IO was returned.
        /// </summary>
        static void OnFileRead(object sender, FileReadEventArgs e)
        {
            Console.WriteLine("FileRead:" + e.FileName + ",offset:" + e.offset + ",readLength:" + e.returnReadLength + ",userName:" + e.UserName + ",processName:" + e.ProcessName);
        }
    }
}