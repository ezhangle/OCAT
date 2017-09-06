﻿
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Frontend
{
    class RegistryUpdater
    {

        const string installDir = "InstallDir";
        const string ocatRegistryKey = @"SOFTWARE\OCAT";

        /// <summary>
        ///  Check for the registry key in the given view.
        ///  Replace InstallDir if the current executable directory is different from the one defined in the registry.
        /// </summary>
        /// <returns>Returns true if the registry was updated.</returns>
        private static bool UpdateExistingInstallDir(RegistryView registryView, string directory)
        {
            using (var view = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, registryView))
            {
                if (view != null)
                {
                    using (var ocat = view.OpenSubKey(ocatRegistryKey, true))
                    {
                        if (ocat != null)
                        {
                            var installDirVal = ocat.GetValue(installDir);
                            // Only change the directory, if it already exists.
                            if (installDirVal != null)
                            {
                                ocat.SetValue(installDir, directory);
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }

        /// <summary>
        ///  Make sure that the InstallDir is set correctly. 
        ///  During devlopment we have to change the registry value on start up.
        /// </summary>
        public static void UpdateInstallDir()
        {
            string directory = AppDomain.CurrentDomain.BaseDirectory;
            // Look for installation directory in 32bit and 64bit registry on the local machine.
            if (UpdateExistingInstallDir(RegistryView.Registry32, directory))
            {
                return;
            }

            if (UpdateExistingInstallDir(RegistryView.Registry64, directory))
            {
                return;
            }

            // Otherwise set the current executable path on current user.
            // This registry entry will not be removed on uninstall.
            using (var ocat = Registry.CurrentUser.CreateSubKey(ocatRegistryKey))
            {
                if (ocat != null)
                {
                    ocat.SetValue(installDir, directory);
                }
            }
        }
    }
}