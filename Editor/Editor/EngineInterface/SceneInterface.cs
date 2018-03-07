﻿using System;
using System.Runtime.InteropServices;

namespace GEPAA_Editor.Engine
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct SceneItem
    {
        public uint GameObjectID;
        public uint GameObjectParentID;
        [MarshalAsAttribute(UnmanagedType.LPStr)]
        public string GameObjectName;
        public uint ComponentCount;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct InspectorField
    {
        [MarshalAsAttribute(UnmanagedType.LPStr)]
        public string FieldName;
        [MarshalAsAttribute(UnmanagedType.LPStr)]
        public string FieldValue;
        public uint GameObjectID;
        public uint ComponentIndex;
        public uint FieldIndex;
    };

    class SceneInterface
    {
        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetGameObjectCount(IntPtr sceneManagerPtr);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr PopulateHierarchyItems(IntPtr sceneManagerPtr, int itemCount);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetComponentFieldCounts(IntPtr sceneManagerPtr, ulong gameObjectID);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr PopulateInspector(IntPtr sceneManagerPtr, ulong gameObjectID, int componentIndex);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RenameGameObject(IntPtr sceneManagerPtr, ulong gameObjectID, string name);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void DeleteGameObject(IntPtr sceneManagerPtr, ulong gameObjectID);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CreateGameObject(IntPtr sceneManagerPtr);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ModifyGameObjectComponentField(IntPtr sceneManagerPtr, ulong gameObjectID, int componentIndex, int fieldIndex, string value);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetParent(IntPtr sceneManagerPtr, ulong childObjectID, ulong parentObjectID);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveParent(IntPtr sceneManagerPtr, ulong gameObjectID);

        [DllImport("GEPAA_Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FreeMemory(IntPtr ptr);
    }
}
