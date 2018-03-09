﻿using System;
using System.Runtime.InteropServices;

namespace GEPAA_Editor.Engine
{
    class EngineInterface
    {
        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr InitaliseEngine(IntPtr window);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetEditorSystem(IntPtr systemsPtr);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetSceneManagerSystem(IntPtr systemsPtr);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void StartUpdateLoop(IntPtr gamePtr);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SaveScene(IntPtr gamePtr, string filePath);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void LoadNewScene(IntPtr gamePtr, string filePath);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PlayStarted(IntPtr gamePtr);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PlayStopped(IntPtr gamePtr);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void CleanD3D(IntPtr gamePtr);

        #region Input

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void LeftMouseClick(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void LeftMouseRelease(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RightMouseClick(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RightMouseRelease(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void MouseMove(IntPtr gamePtr, int xPos, int yPos);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void KeyDown(IntPtr gamePtr, int keyCode);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void KeyUp(IntPtr gamePtr, int keyCode);

        #endregion

    }
}
