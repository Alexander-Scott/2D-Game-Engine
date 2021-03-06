﻿using GEPAA_Editor.Engine;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace GEPAA_Editor.EditorControls
{
    // TODO: Store a map of Y cell indexes and the component value they map to. 
    // When cell change

    public class Inspector
    {
        private DataGridView _view;

        private Dictionary<int, InspectorField> _cellToComponentMap;

        private Scene _scene;
        private IntPtr _sceneManager;

        public Inspector(DataGridView dgv)
        {
            _view = dgv;

            _cellToComponentMap = new Dictionary<int, InspectorField>();

            _view.BackgroundColor = System.Drawing.Color.White;
            _view.RowHeadersVisible = false;
            _view.ColumnHeadersVisible = false;

            _view.CellValueChanged += _view_CellValueChanged;

            _view.Columns.Clear();
            _view.Columns.Add("Name", "Name");
            _view.Columns[0].ReadOnly = true;
            _view.Columns.Add("Value", "Value");
        }

        public void SetScene(Scene scene)
        {
            _scene = scene;
        }

        private void _view_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            InspectorField fieldChanged = _cellToComponentMap[e.RowIndex];
            SceneInterface.ModifyGameObjectComponentField(_sceneManager, fieldChanged.GameObjectID,
                (int)fieldChanged.ComponentIndex, (int)fieldChanged.FieldIndex, _view[e.ColumnIndex, e.RowIndex].Value.ToString());
            _scene.HasChanged = true;
        }

        public void GameObjectClicked(IntPtr sceneManager, int id, int componentCount)
        {
            _sceneManager = sceneManager;

            ClearInspector();

            // First work out how many fields each component has
            IntPtr fieldCountPtr = SceneInterface.GetComponentFieldCounts(sceneManager, (ulong)id);
            int intSize = sizeof(int);

            int[] fieldCount = new int[componentCount];
            for (int i = 0; i < componentCount; i++)
            {
                IntPtr data = new IntPtr(fieldCountPtr.ToInt64() + intSize * i);
                fieldCount[i] = (int)Marshal.PtrToStructure(data, typeof(int));
            }

            for (int i = 0; i < componentCount; i++)
            {
                IntPtr fieldsPtr = SceneInterface.PopulateInspector(sceneManager, (ulong)id, i);
                int structSize = Marshal.SizeOf(typeof(InspectorField));

                for (int j = 0; j < fieldCount[i]; j++)
                {
                    // Parse the data recieved from the engine
                    IntPtr data = new IntPtr(fieldsPtr.ToInt64() + structSize * j);
                    InspectorField field = (InspectorField)Marshal.PtrToStructure(data, typeof(InspectorField));

                    _cellToComponentMap.Add(_view.Rows.Count, field);

                    _view.Rows.Add(field.FieldName, field.FieldValue);
                }

                if (i != componentCount - 1)
                    _view.Rows.Add("", ""); // Add gap between components

                SceneInterface.FreeMemory(fieldsPtr);
            }

            SceneInterface.FreeMemory(fieldCountPtr);
        }

        public void ClearInspector()
        {
            _view.Rows.Clear();
            _cellToComponentMap.Clear();
        }
    }
}