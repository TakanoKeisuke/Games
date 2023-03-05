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
 104;
 -9.98762;0.22287;-0.00963;,
 -9.98762;20.22287;9.99037;,
 -2.91655;0.22287;2.91931;,
 -9.98762;20.22287;9.99037;,
 0.01238;0.22287;9.99037;,
 -9.98762;20.22287;9.99037;,
 -2.91655;0.22287;17.06143;,
 -9.98762;20.22287;9.99037;,
 -9.98762;0.22287;19.99036;,
 -9.98762;20.22287;9.99037;,
 -17.05869;0.22287;17.06143;,
 -9.98762;20.22287;9.99037;,
 -19.98762;0.22287;9.99037;,
 -9.98762;20.22287;9.99037;,
 -17.05869;0.22287;2.91931;,
 -9.98762;20.22287;9.99037;,
 -9.98762;0.22287;-0.00963;,
 -9.98762;0.22287;9.99037;,
 -9.98762;0.22287;-0.00963;,
 -2.91655;0.22287;2.91931;,
 0.01238;0.22287;9.99037;,
 -2.91655;0.22287;17.06143;,
 -9.98762;0.22287;19.99036;,
 -17.05869;0.22287;17.06143;,
 -19.98762;0.22287;9.99037;,
 -17.05869;0.22287;2.91931;,
 9.95843;0.22287;-0.00963;,
 9.95843;20.22287;9.99037;,
 17.02950;0.22287;2.91931;,
 9.95843;20.22287;9.99037;,
 19.95843;0.22287;9.99037;,
 9.95843;20.22287;9.99037;,
 17.02950;0.22287;17.06143;,
 9.95843;20.22287;9.99037;,
 9.95843;0.22287;19.99036;,
 9.95843;20.22287;9.99037;,
 2.88736;0.22287;17.06143;,
 9.95843;20.22287;9.99037;,
 -0.04157;0.22287;9.99037;,
 9.95843;20.22287;9.99037;,
 2.88736;0.22287;2.91931;,
 9.95843;20.22287;9.99037;,
 9.95843;0.22287;-0.00963;,
 9.95843;0.22287;9.99037;,
 9.95843;0.22287;-0.00963;,
 17.02950;0.22287;2.91931;,
 19.95843;0.22287;9.99037;,
 17.02950;0.22287;17.06143;,
 9.95843;0.22287;19.99036;,
 2.88736;0.22287;17.06143;,
 -0.04157;0.22287;9.99037;,
 2.88736;0.22287;2.91931;,
 -9.98762;0.22287;-20.06408;,
 -9.98762;20.22287;-10.06408;,
 -2.91655;0.22287;-17.13515;,
 -9.98762;20.22287;-10.06408;,
 0.01238;0.22287;-10.06408;,
 -9.98762;20.22287;-10.06408;,
 -2.91655;0.22287;-2.99302;,
 -9.98762;20.22287;-10.06408;,
 -9.98762;0.22287;-0.06410;,
 -9.98762;20.22287;-10.06408;,
 -17.05869;0.22287;-2.99302;,
 -9.98762;20.22287;-10.06408;,
 -19.98762;0.22287;-10.06408;,
 -9.98762;20.22287;-10.06408;,
 -17.05869;0.22287;-17.13515;,
 -9.98762;20.22287;-10.06408;,
 -9.98762;0.22287;-20.06408;,
 -9.98762;0.22287;-10.06408;,
 -9.98762;0.22287;-20.06408;,
 -2.91655;0.22287;-17.13515;,
 0.01238;0.22287;-10.06408;,
 -2.91655;0.22287;-2.99302;,
 -9.98762;0.22287;-0.06410;,
 -17.05869;0.22287;-2.99302;,
 -19.98762;0.22287;-10.06408;,
 -17.05869;0.22287;-17.13515;,
 10.01263;0.22287;-20.06408;,
 10.01263;20.22287;-10.06408;,
 17.08370;0.22287;-17.13515;,
 10.01263;20.22287;-10.06408;,
 20.01263;0.22287;-10.06408;,
 10.01263;20.22287;-10.06408;,
 17.08370;0.22287;-2.99302;,
 10.01263;20.22287;-10.06408;,
 10.01262;0.22287;-0.06410;,
 10.01263;20.22287;-10.06408;,
 2.94156;0.22287;-2.99302;,
 10.01263;20.22287;-10.06408;,
 0.01262;0.22287;-10.06408;,
 10.01263;20.22287;-10.06408;,
 2.94156;0.22287;-17.13515;,
 10.01263;20.22287;-10.06408;,
 10.01263;0.22287;-20.06408;,
 10.01263;0.22287;-10.06408;,
 10.01263;0.22287;-20.06408;,
 17.08370;0.22287;-17.13515;,
 20.01263;0.22287;-10.06408;,
 17.08370;0.22287;-2.99302;,
 10.01262;0.22287;-0.06410;,
 2.94156;0.22287;-2.99302;,
 0.01262;0.22287;-10.06408;,
 2.94156;0.22287;-17.13515;;
 
 64;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;6,7,8;,
 3;8,9,10;,
 3;10,11,12;,
 3;12,13,14;,
 3;14,15,16;,
 3;17,18,19;,
 3;17,19,20;,
 3;17,20,21;,
 3;17,21,22;,
 3;17,22,23;,
 3;17,23,24;,
 3;17,24,25;,
 3;17,25,18;,
 3;26,27,28;,
 3;28,29,30;,
 3;30,31,32;,
 3;32,33,34;,
 3;34,35,36;,
 3;36,37,38;,
 3;38,39,40;,
 3;40,41,42;,
 3;43,44,45;,
 3;43,45,46;,
 3;43,46,47;,
 3;43,47,48;,
 3;43,48,49;,
 3;43,49,50;,
 3;43,50,51;,
 3;43,51,44;,
 3;52,53,54;,
 3;54,55,56;,
 3;56,57,58;,
 3;58,59,60;,
 3;60,61,62;,
 3;62,63,64;,
 3;64,65,66;,
 3;66,67,68;,
 3;69,70,71;,
 3;69,71,72;,
 3;69,72,73;,
 3;69,73,74;,
 3;69,74,75;,
 3;69,75,76;,
 3;69,76,77;,
 3;69,77,70;,
 3;78,79,80;,
 3;80,81,82;,
 3;82,83,84;,
 3;84,85,86;,
 3;86,87,88;,
 3;88,89,90;,
 3;90,91,92;,
 3;92,93,94;,
 3;95,96,97;,
 3;95,97,98;,
 3;95,98,99;,
 3;95,99,100;,
 3;95,100,101;,
 3;95,101,102;,
 3;95,102,103;,
 3;95,103,96;;
 
 MeshMaterialList {
  5;
  64;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.530400;0.344800;0.140800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.501600;0.501600;0.501600;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.759200;0.520800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  31;
  -0.000000;0.447214;-0.894427;,
  0.632455;0.447214;-0.632456;,
  0.894427;0.447214;0.000000;,
  0.632455;0.447213;0.632456;,
  -0.000000;0.447213;0.894427;,
  -0.632455;0.447213;0.632456;,
  -0.894427;0.447214;0.000000;,
  -0.632456;0.447214;-0.632456;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;0.447214;-0.894427;,
  0.632455;0.447214;-0.632456;,
  0.894427;0.447214;0.000000;,
  0.632455;0.447214;0.632456;,
  -0.000000;0.447213;0.894427;,
  -0.632455;0.447213;0.632456;,
  -0.894427;0.447214;0.000000;,
  -0.632455;0.447214;-0.632456;,
  -0.000000;0.447214;-0.894427;,
  0.632456;0.447214;-0.632456;,
  0.894427;0.447214;0.000000;,
  -0.000000;0.447213;0.894427;,
  -0.632455;0.447213;0.632456;,
  -0.632456;0.447214;-0.632455;,
  -0.000000;0.447214;-0.894427;,
  0.632456;0.447214;-0.632455;,
  0.894427;0.447214;0.000000;,
  0.632455;0.447214;0.632456;,
  -0.000000;0.447213;0.894427;,
  -0.632455;0.447213;0.632456;,
  -0.894427;0.447214;0.000000;,
  -0.632455;0.447214;-0.632456;;
  64;
  3;0,1,1;,
  3;1,1,2;,
  3;2,3,3;,
  3;3,3,4;,
  3;4,5,5;,
  3;5,5,6;,
  3;6,7,7;,
  3;7,7,0;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;9,10,10;,
  3;10,10,11;,
  3;11,12,12;,
  3;12,12,13;,
  3;13,14,14;,
  3;14,14,15;,
  3;15,16,16;,
  3;16,16,9;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;17,18,18;,
  3;18,18,19;,
  3;19,3,3;,
  3;3,3,20;,
  3;20,21,21;,
  3;21,21,6;,
  3;6,22,22;,
  3;22,22,17;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;23,24,24;,
  3;24,24,25;,
  3;25,26,26;,
  3;26,26,27;,
  3;27,28,28;,
  3;28,28,29;,
  3;29,30,30;,
  3;30,30,23;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;;
 }
 MeshTextureCoords {
  104;
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
