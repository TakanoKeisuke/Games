xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 34;
 0.00000;0.00000;0.00000;,
 0.00000;-0.64812;-2.01279;,
 -2.14240;-0.64812;-1.42326;,
 0.00000;0.00000;0.00000;,
 -3.02981;-0.64812;0.00000;,
 0.00000;0.00000;0.00000;,
 -2.14240;-0.64812;1.42326;,
 0.00000;0.00000;0.00000;,
 0.00000;-0.64812;2.01279;,
 0.00000;0.00000;0.00000;,
 2.14240;-0.64812;1.42326;,
 0.00000;0.00000;0.00000;,
 3.02981;-0.64812;-0.00000;,
 0.00000;0.00000;0.00000;,
 2.14240;-0.64812;-1.42326;,
 0.00000;0.00000;0.00000;,
 0.00000;-0.64812;-2.01279;,
 0.00000;-2.46411;-3.62692;,
 -3.86048;-2.46411;-2.56462;,
 -5.45954;-2.46411;0.00000;,
 -3.86048;-2.46411;2.56462;,
 0.00000;-2.46411;3.62692;,
 3.86048;-2.46411;2.56462;,
 5.45954;-2.46411;-0.00000;,
 3.86048;-2.46411;-2.56462;,
 0.00000;-2.46411;-3.62692;,
 0.01281;-2.45612;-0.01568;,
 0.01281;-2.45612;-0.01568;,
 0.01281;-2.45612;-0.01568;,
 0.01281;-2.45612;-0.01568;,
 0.01281;-2.45612;-0.01568;,
 0.01281;-2.45612;-0.01568;,
 0.01281;-2.45612;-0.01568;,
 0.01281;-2.45612;-0.01568;;
 
 24;
 3;0,1,2;,
 3;3,2,4;,
 3;5,4,6;,
 3;7,6,8;,
 3;9,8,10;,
 3;11,10,12;,
 3;13,12,14;,
 3;15,14,16;,
 4;1,17,18,2;,
 4;2,18,19,4;,
 4;4,19,20,6;,
 4;6,20,21,8;,
 4;8,21,22,10;,
 4;10,22,23,12;,
 4;12,23,24,14;,
 4;14,24,25,16;,
 3;26,25,24;,
 3;27,24,23;,
 3;28,23,22;,
 3;29,22,21;,
 3;30,19,18;,
 3;31,21,20;,
 3;32,18,17;,
 3;33,20,19;;
 
 MeshMaterialList {
  4;
  24;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.501961;0.018824;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.467451;0.467451;0.467451;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Downloads\\2.png";
   }
  }
 }
 MeshNormals {
  26;
  0.000000;1.000000;-0.000000;,
  0.000000;0.838917;-0.544259;,
  -0.277427;0.873859;-0.399257;,
  -0.407828;0.913059;0.000000;,
  -0.277427;0.873859;0.399257;,
  0.000000;0.838917;0.544259;,
  0.277427;0.873859;0.399257;,
  0.407828;0.913059;0.000000;,
  0.277427;0.873859;-0.399257;,
  -0.000002;-1.000000;0.000006;,
  0.000000;0.664345;-0.747426;,
  -0.395531;0.726982;-0.561295;,
  -0.598670;0.800996;0.000000;,
  -0.395531;0.726982;0.561295;,
  0.000000;0.664345;0.747426;,
  0.395531;0.726982;0.561295;,
  0.598670;0.800996;0.000000;,
  0.395531;0.726982;-0.561295;,
  -0.000001;-0.999998;0.002215;,
  -0.001041;-0.999998;0.001567;,
  -0.001468;-0.999999;0.000002;,
  -0.001035;-0.999998;-0.001556;,
  -0.000001;-0.999998;-0.002196;,
  0.001462;-0.999999;0.000002;,
  0.001037;-0.999998;0.001563;,
  0.001031;-0.999998;-0.001552;;
  24;
  3;0,1,2;,
  3;0,2,3;,
  3;0,3,4;,
  3;0,4,5;,
  3;0,5,6;,
  3;0,6,7;,
  3;0,7,8;,
  3;0,8,1;,
  4;1,10,11,2;,
  4;2,11,12,3;,
  4;3,12,13,4;,
  4;4,13,14,5;,
  4;5,14,15,6;,
  4;6,15,16,7;,
  4;7,16,17,8;,
  4;8,17,10,1;,
  3;9,18,19;,
  3;9,19,20;,
  3;9,20,21;,
  3;9,21,22;,
  3;9,23,24;,
  3;9,22,25;,
  3;9,24,18;,
  3;9,25,23;;
 }
 MeshTextureCoords {
  34;
  0.062500;0.000000;,
  0.000000;0.142857;,
  0.125000;0.142857;,
  0.187500;0.000000;,
  0.250000;0.142857;,
  0.312500;0.000000;,
  0.375000;0.142857;,
  0.437500;0.000000;,
  0.500000;0.142857;,
  0.562500;0.000000;,
  0.625000;0.142857;,
  0.687500;0.000000;,
  0.750000;0.142857;,
  0.812500;0.000000;,
  0.875000;0.142857;,
  0.937500;0.000000;,
  1.000000;0.142857;,
  0.000000;0.285714;,
  0.125000;0.285714;,
  0.250000;0.285714;,
  0.375000;0.285714;,
  0.500000;0.285714;,
  0.625000;0.285714;,
  0.750000;0.285714;,
  0.875000;0.285714;,
  1.000000;0.285714;,
  0.937500;0.142857;,
  0.812500;0.142857;,
  0.687500;0.142857;,
  0.562500;0.142857;,
  0.187500;0.142857;,
  0.437500;0.142857;,
  0.062500;0.142857;,
  0.312500;0.142857;;
 }
}
