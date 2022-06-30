#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "Std_types.h"
#include "BL.h"
#include "UsartHal.h"
#include "flash.h"

//char arr[11]={'a','b','d','e','l','r','a','h','m','a','n'};
char arr1[11];
char arr[]={0, 0, 1, 32, 197, 2, 1, 8, 205, 2, 1, 8, 209, 2, 1, 8, 69, 3, 1, 8, 73, 3, 1, 8, 145, 3, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 217, 3, 1, 8, 221, 3, 1, 8, 0, 0, 0, 0, 225, 3, 1, 8, 229, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 49, 13, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 253, 11, 1, 8, 169, 12, 1, 8, 0, 0, 0, 0, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 245, 3, 1, 8, 0, 0, 0, 0, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 185, 12, 1, 8, 245, 3, 1, 8, 245, 3, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 245, 3, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 245, 3, 1, 8, 0, 181, 131, 176, 0, 240, 188, 249, 56, 75, 57, 74, 19, 96, 57, 74, 19, 96, 57, 73, 12, 224, 10, 104, 75, 104, 1, 241, 12, 4, 136, 104, 3, 224, 17, 104, 25, 96, 4, 51, 4, 50, 152, 66, 249, 216, 33, 70, 50, 75, 153, 66, 239, 211, 46, 75, 26, 104, 49, 75, 154, 66, 4, 209, 44, 75, 26, 104, 47, 75, 154, 66, 0, 208, 254, 231, 39, 75, 46, 74, 19, 96, 46, 74, 19, 96, 46, 75, 10, 224, 25, 70, 81, 248, 8, 43, 91, 104, 2, 224, 0, 32, 16, 96, 4, 50, 154, 66, 250, 211, 11, 70, 40, 74, 147, 66, 241, 211, 36, 75, 27, 104, 19, 185, 35, 75, 27, 104, 3, 177, 254, 231, 0, 240, 136, 249, 105, 70, 1, 168, 0, 240, 34, 249, 33, 76, 34, 75, 28, 27, 164, 16, 0, 37, 4, 224, 30, 75, 83, 248, 37, 48, 152, 71, 1, 53, 172, 66, 248, 220, 29, 76, 29, 75, 28, 27, 164, 16, 0, 37, 4, 224, 26, 75, 83, 248, 37, 48, 152, 71, 1, 53, 172, 66, 248, 220, 0, 153, 1, 152, 0, 240, 146, 253, 5, 70, 22, 76, 22, 75, 28, 27, 164, 16, 4, 224, 1, 60, 19, 75, 83, 248, 36, 48, 152, 71, 0, 44, 248, 220, 40, 70, 0, 240, 208, 248, 186, 186, 222, 202, 0, 0, 0, 32, 152, 0, 0, 32, 248, 3, 1, 8, 16, 4, 1, 8, 120, 86, 52, 18, 50, 84, 118, 152, 156, 0, 0, 32, 192, 1, 0, 32, 16, 4, 1, 8, 32, 4, 1, 8, 32, 4, 1, 8, 32, 4, 1, 8, 32, 4, 1, 8, 32, 4, 1, 8, 32, 4, 1, 8, 32, 4, 1, 8, 8, 181, 255, 247, 101, 255, 0, 191, 0, 190, 254, 231, 30, 240, 4, 15, 12, 191, 239, 243, 8, 128, 239, 243, 9, 128, 113, 70, 65, 74, 16, 71, 45, 233, 240, 65, 130, 176, 4, 70, 136, 70, 19, 75, 94, 107, 159, 107, 157, 106, 27, 107, 19, 240, 2, 15, 13, 208, 15, 75, 219, 106, 0, 43, 9, 218, 75, 246, 171, 97, 0, 240, 139, 249, 32, 177, 79, 240, 0, 66, 9, 75, 218, 98, 12, 224, 9, 72, 0, 240, 172, 248, 205, 248, 0, 128, 59, 70, 50, 70, 41, 70, 32, 70, 0, 240, 2, 249, 0, 190, 254, 231, 2, 176, 189, 232, 240, 129, 0, 191, 0, 237, 0, 224, 180, 24, 1, 8, 0, 190, 254, 231, 30, 240, 4, 15, 12, 191, 239, 243, 8, 128, 239, 243, 9, 128, 113, 70, 36, 74, 16, 71, 45, 233, 240, 65, 130, 176, 4, 70, 136, 70, 8, 75, 94, 107, 159, 107, 157, 106, 7, 72, 0, 240, 130, 248, 205, 248, 0, 128, 59, 70, 50, 70, 41, 70, 32, 70, 0, 240, 216, 248, 0, 190, 254, 231, 0, 237, 0, 224, 196, 24, 1, 8, 30, 240, 4, 15, 12, 191, 239, 243, 8, 128, 239, 243, 9, 128, 113, 70, 19, 74, 16, 71, 45, 233, 240, 65, 130, 176, 4, 70, 136, 70, 8, 75, 94, 107, 159, 107, 157, 106, 7, 72, 0, 240, 94, 248, 205, 248, 0, 128, 59, 70, 50, 70, 41, 70, 32, 70, 0, 240, 180, 248, 0, 190, 254, 231, 0, 237, 0, 224, 208, 24, 1, 8, 0, 190, 254, 231, 0, 190, 254, 231, 0, 190, 254, 231, 112, 71, 0, 0, 229, 2, 1, 8, 93, 3, 1, 8, 165, 3, 1, 8, 0, 190, 254, 231, 48, 26, 1, 8, 0, 0, 0, 32, 156, 0, 0, 32, 48, 26, 1, 8, 0, 0, 0, 16, 0, 0, 0, 16, 156, 0, 0, 32, 196, 1, 0, 32, 0, 0, 0, 16, 0, 0, 0, 16, 254, 231, 0, 191, 8, 181, 13, 75, 27, 104, 19, 185, 12, 74, 11, 75, 26, 96, 10, 75, 26, 104, 195, 28, 35, 240, 3, 3, 19, 68, 9, 73, 139, 66, 6, 217, 0, 240, 26, 253, 12, 35, 3, 96, 79, 240, 255, 48, 8, 189, 2, 73, 11, 96, 16, 70, 8, 189, 0, 191, 160, 0, 0, 32, 196, 1, 0, 32, 0, 252, 0, 32, 1, 35, 3, 96, 1, 75, 11, 96, 112, 71, 0, 191, 4, 0, 0, 32, 15, 180, 0, 181, 131, 176, 4, 171, 83, 248, 4, 43, 1, 147, 128, 33, 6, 72, 0, 240, 41, 253, 0, 40, 3, 221, 1, 70, 3, 72, 0, 240, 57, 248, 3, 176, 93, 248, 4, 235, 4, 176, 112, 71, 168, 0, 0, 32, 45, 233, 240, 67, 133, 176, 4, 70, 15, 70, 67, 86, 19, 187, 4, 37, 40, 70, 33, 70, 171, 190, 4, 70, 31, 224, 53, 70, 16, 46, 40, 191, 16, 37, 0, 35, 6, 224, 20, 249, 1, 27, 4, 170, 26, 68, 2, 248, 16, 28, 1, 51, 171, 66, 246, 211, 4, 170, 19, 68, 0, 34, 3, 248, 16, 44, 233, 70, 79, 240, 4, 8, 64, 70, 73, 70, 171, 190, 128, 70, 118, 27, 0, 224, 14, 70, 0, 46, 223, 209, 56, 70, 5, 176, 189, 232, 240, 131, 0, 191, 8, 181, 255, 247, 203, 255, 8, 189, 8, 181, 0, 240, 149, 248, 2, 75, 2, 74, 154, 96, 8, 189, 0, 191, 0, 237, 0, 224, 0, 0, 1, 8, 8, 181, 0, 240, 169, 248, 8, 189, 248, 181, 4, 70, 13, 70, 23, 70, 30, 70, 38, 72, 255, 247, 154, 255, 33, 104, 37, 72, 255, 247, 150, 255, 97, 104, 36, 72, 255, 247, 146, 255, 161, 104, 35, 72, 255, 247, 142, 255, 225, 104, 34, 72, 255, 247, 138, 255, 33, 105, 33, 72, 255, 247, 134, 255, 97, 105, 32, 72, 255, 247, 130, 255, 161, 105, 31, 72, 255, 247, 126, 255, 225, 105, 30, 72, 255, 247, 122, 255, 29, 72, 255, 247, 119, 255, 41, 70, 28, 72, 255, 247, 115, 255, 28, 76, 225, 106, 28, 72, 255, 247, 110, 255, 33, 107, 27, 72, 255, 247, 106, 255, 225, 107, 26, 72, 255, 247, 102, 255, 21, 240, 128, 15, 3, 208, 57, 70, 23, 72, 255, 247, 95, 255, 21, 244, 0, 79, 3, 208, 49, 70, 21, 72, 255, 247, 88, 255, 20, 72, 255, 247, 85, 255, 6, 153, 19, 72, 255, 247, 81, 255, 248, 189, 152, 23, 1, 8, 168, 23, 1, 8, 184, 23, 1, 8, 200, 23, 1, 8, 216, 23, 1, 8, 232, 23, 1, 8, 248, 23, 1, 8, 8, 24, 1, 8, 24, 24, 1, 8, 40, 24, 1, 8, 52, 24, 1, 8, 0, 237, 0, 224, 68, 24, 1, 8, 84, 24, 1, 8, 100, 24, 1, 8, 116, 24, 1, 8, 132, 24, 1, 8, 148, 24, 1, 8, 156, 24, 1, 8, 131, 105, 26, 136, 138, 66, 7, 209, 2, 104, 3, 58, 1, 42, 5, 216, 2, 51, 131, 97, 1, 32, 112, 71, 0, 32, 112, 71, 0, 32, 112, 71, 12, 75, 26, 104, 66, 240, 1, 2, 26, 96, 0, 33, 153, 96, 26, 104, 34, 240, 132, 114, 34, 244, 128, 50, 26, 96, 7, 74, 90, 96, 26, 104, 34, 244, 128, 34, 26, 96, 217, 96, 79, 240, 0, 98, 3, 75, 154, 96, 112, 71, 0, 191, 0, 56, 2, 64, 16, 48, 0, 36, 0, 237, 0, 224, 34, 75, 155, 104, 3, 240, 12, 3, 4, 43, 7, 208, 8, 43, 9, 208, 0, 43, 45, 209, 30, 74, 31, 75, 26, 96, 44, 224, 30, 74, 29, 75, 26, 96, 40, 224, 25, 75, 90, 104, 91, 104, 3, 240, 63, 3, 18, 244, 128, 15, 9, 208, 24, 74, 178, 251, 243, 242, 20, 75, 91, 104, 195, 243, 136, 19, 3, 251, 2, 242, 8, 224, 17, 74, 178, 251, 243, 243, 15, 74, 81, 104, 193, 243, 136, 17, 1, 251, 3, 242, 12, 75, 91, 104, 195, 243, 1, 67, 1, 51, 91, 0, 178, 251, 243, 243, 10, 74, 19, 96, 2, 224, 7, 74, 8, 75, 26, 96, 5, 75, 155, 104, 195, 243, 3, 19, 7, 74, 209, 92, 4, 74, 19, 104, 203, 64, 19, 96, 112, 71, 0, 56, 2, 64, 0, 36, 244, 0, 12, 0, 0, 32, 64, 120, 125, 1, 224, 24, 1, 8, 45, 233, 240, 65, 3, 70, 136, 70, 0, 32, 0, 33, 0, 34, 25, 224, 19, 240, 1, 6, 19, 208, 182, 178, 8, 251, 2, 247, 167, 241, 32, 12, 199, 241, 32, 14, 0, 37, 6, 250, 12, 252, 69, 234, 12, 5, 38, 250, 14, 254, 69, 234, 14, 5, 6, 250, 7, 244, 32, 67, 41, 67, 91, 8, 1, 50, 210, 178, 0, 43, 227, 209, 189, 232, 240, 129, 56, 181, 3, 104, 19, 240, 64, 79, 64, 240, 135, 128, 22, 43, 0, 242, 134, 128, 66, 104, 2, 240, 64, 65, 177, 241, 128, 79, 64, 240, 129, 128, 3, 49, 138, 66, 127, 216, 130, 104, 2, 240, 64, 65, 177, 241, 0, 79, 123, 209, 178, 241, 128, 47, 122, 216, 1, 105, 65, 76, 161, 66, 19, 208, 4, 245, 128, 100, 161, 66, 15, 208, 4, 245, 128, 100, 161, 66, 11, 208, 4, 245, 128, 100, 161, 66, 7, 208, 4, 245, 128, 100, 161, 66, 3, 208, 4, 245, 64, 100, 161, 66, 100, 209, 196, 104, 4, 240, 64, 69, 181, 241, 64, 79, 96, 209, 15, 53, 172, 66, 95, 216, 4, 70, 72, 104, 195, 243, 128, 3, 149, 178, 3, 251, 5, 243, 3, 67, 75, 96, 2, 33, 40, 70, 255, 247, 144, 255, 37, 105, 43, 104, 0, 235, 64, 2, 210, 67, 3, 234, 2, 1, 35, 104, 3, 240, 3, 3, 3, 251, 0, 243, 11, 67, 43, 96, 37, 105, 235, 104, 2, 234, 3, 1, 35, 104, 195, 243, 193, 3, 3, 251, 0, 243, 11, 67, 235, 96, 33, 105, 139, 104, 26, 64, 99, 104, 3, 240, 3, 3, 3, 251, 0, 243, 19, 67, 139, 96, 4, 33, 128, 178, 255, 247, 105, 255, 37, 105, 43, 106, 192, 235, 0, 18, 35, 234, 2, 3, 226, 104, 2, 240, 15, 2, 2, 251, 0, 242, 26, 67, 42, 98, 37, 105, 106, 106, 193, 235, 1, 19, 34, 234, 3, 0, 226, 104, 2, 240, 15, 2, 2, 251, 1, 243, 3, 67, 107, 98, 0, 32, 56, 189, 1, 32, 56, 189, 1, 32, 56, 189, 2, 32, 56, 189, 2, 32, 56, 189, 3, 32, 56, 189, 3, 32, 56, 189, 4, 32, 56, 189, 5, 32, 56, 189, 5, 32, 56, 189, 0, 191, 0, 0, 2, 64, 131, 104, 3, 240, 64, 66, 178, 241, 0, 79, 36, 209, 179, 241, 128, 47, 35, 216, 2, 105, 20, 72, 130, 66, 19, 208, 0, 245, 128, 96, 130, 66, 15, 208, 0, 245, 128, 96, 130, 66, 11, 208, 0, 245, 128, 96, 130, 66, 7, 208, 0, 245, 128, 96, 130, 66, 3, 208, 0, 245, 64, 96, 130, 66, 13, 209, 9, 177, 16, 41, 12, 209, 35, 240, 64, 67, 3, 250, 1, 241, 145, 97, 0, 32, 112, 71, 3, 32, 112, 71, 3, 32, 112, 71, 4, 32, 112, 71, 6, 32, 112, 71, 0, 191, 0, 0, 2, 64, 48, 181, 135, 176, 79, 240, 128, 67, 2, 147, 79, 240, 64, 67, 4, 147, 0, 36, 27, 224, 35, 70, 4, 235, 68, 1, 138, 0, 13, 73, 10, 68, 82, 122, 18, 185, 1, 34, 1, 146, 1, 224, 5, 34, 1, 146, 9, 73, 88, 0, 197, 24, 170, 0, 21, 70, 10, 68, 82, 104, 3, 146, 75, 89, 5, 147, 1, 168, 255, 247, 4, 255, 1, 52, 228, 178, 2, 44, 225, 217, 7, 176, 48, 189, 16, 0, 0, 32, 48, 181, 135, 176, 12, 74, 68, 0, 37, 24, 171, 0, 213, 24, 109, 104, 3, 149, 211, 88, 5, 147, 32, 68, 131, 0, 19, 68, 27, 122, 139, 66, 4, 209, 16, 33, 1, 168, 255, 247, 137, 255, 3, 224, 0, 33, 1, 168, 255, 247, 132, 255, 7, 176, 48, 189, 16, 0, 0, 32, 66, 9, 0, 240, 31, 0, 1, 35, 3, 250, 0, 240, 3, 75, 2, 241, 96, 1, 67, 248, 33, 0, 67, 248, 34, 0, 112, 71, 0, 225, 0, 224, 2, 74, 19, 107, 24, 67, 16, 99, 112, 71, 0, 191, 0, 56, 2, 64, 2, 74, 83, 108, 24, 67, 80, 100, 112, 71, 0, 191, 0, 56, 2, 64, 1, 74, 2, 75, 26, 96, 112, 71, 4, 0, 250, 5, 12, 237, 0, 224, 0, 0, 0, 0, 0, 40, 102, 208, 48, 180, 1, 70, 208, 233, 0, 35, 58, 165, 213, 233, 0, 69, 171, 66, 8, 191, 162, 66, 11, 208, 53, 76, 1, 37, 171, 66, 8, 191, 162, 66, 5, 208, 51, 76, 2, 37, 171, 66, 8, 191, 162, 66, 81, 209, 136, 104, 176, 245, 128, 63, 79, 210, 200, 104, 16, 177, 176, 245, 0, 95, 76, 209, 8, 105, 48, 244, 64, 112, 74, 209, 72, 105, 8, 40, 9, 208, 4, 40, 7, 208, 12, 40, 5, 208, 136, 40, 3, 208, 68, 40, 1, 208, 204, 40, 63, 209, 209, 233, 6, 69, 84, 234, 5, 0, 4, 208, 0, 45, 8, 191, 180, 245, 128, 95, 55, 209, 211, 104, 67, 244, 0, 83, 211, 96, 147, 104, 27, 12, 27, 4, 147, 96, 144, 104, 139, 104, 3, 67, 147, 96, 19, 105, 35, 244, 64, 83, 19, 97, 16, 105, 203, 104, 3, 67, 19, 97, 211, 104, 35, 244, 152, 83, 35, 240, 12, 3, 211, 96, 212, 104, 11, 105, 72, 105, 0, 240, 15, 0, 24, 67, 139, 105, 3, 67, 35, 67, 211, 96, 80, 105, 75, 105, 3, 240, 240, 3, 3, 67, 83, 97, 0, 32, 12, 224, 1, 32, 112, 71, 3, 32, 8, 224, 2, 32, 6, 224, 4, 32, 4, 224, 5, 32, 2, 224, 6, 32, 0, 224, 7, 32, 48, 188, 112, 71, 0, 68, 0, 64, 0, 20, 1, 64, 0, 16, 1, 64, 0, 0, 0, 0, 240, 180, 208, 233, 0, 69, 80, 179, 5, 240, 3, 3, 73, 179, 28, 167, 215, 233, 0, 103, 189, 66, 8, 191, 180, 66, 11, 208, 20, 78, 1, 39, 189, 66, 8, 191, 180, 66, 5, 208, 18, 78, 2, 39, 189, 66, 8, 191, 180, 66, 24, 209, 16, 76, 4, 235, 3, 20, 228, 104, 172, 185, 15, 78, 28, 1, 53, 25, 0, 35, 171, 96, 1, 39, 239, 96, 49, 81, 106, 96, 1, 104, 202, 104, 66, 240, 32, 2, 202, 96, 24, 70, 6, 224, 1, 32, 4, 224, 1, 32, 2, 224, 3, 32, 0, 224, 9, 32, 240, 188, 112, 71, 0, 68, 0, 64, 0, 20, 1, 64, 124, 1, 0, 32, 76, 1, 0, 32, 0, 16, 1, 64, 0, 0, 0, 0, 112, 180, 157, 248, 12, 16, 248, 177, 6, 70, 22, 165, 213, 233, 0, 69, 171, 66, 8, 191, 162, 66, 11, 208, 15, 76, 1, 37, 171, 66, 8, 191, 162, 66, 5, 208, 13, 76, 2, 37, 171, 66, 8, 191, 162, 66, 13, 209, 2, 41, 13, 216, 3, 240, 3, 3, 3, 235, 67, 3, 25, 68, 8, 75, 67, 248, 33, 96, 0, 32, 4, 224, 1, 32, 2, 224, 3, 32, 0, 224, 8, 32, 112, 188, 112, 71, 0, 191, 0, 68, 0, 64, 0, 20, 1, 64, 40, 1, 0, 32, 0, 16, 1, 64, 0, 0, 0, 0, 16, 181, 38, 75, 28, 104, 27, 104, 19, 240, 128, 15, 1, 208, 35, 75, 219, 104, 34, 75, 27, 104, 19, 240, 64, 15, 29, 208, 31, 75, 219, 104, 19, 240, 64, 15, 24, 208, 30, 75, 154, 104, 91, 104, 154, 66, 11, 209, 0, 34, 27, 75, 218, 96, 27, 75, 91, 104, 152, 71, 23, 74, 211, 104, 35, 240, 64, 3, 211, 96, 7, 224, 21, 75, 25, 104, 154, 104, 80, 28, 152, 96, 138, 92, 17, 75, 90, 96, 20, 240, 32, 15, 28, 208, 15, 75, 219, 104, 19, 240, 32, 15, 23, 208, 15, 75, 25, 104, 154, 104, 80, 28, 152, 96, 10, 72, 64, 104, 136, 84, 154, 104, 91, 104, 154, 66, 11, 209, 0, 34, 9, 75, 218, 96, 7, 75, 155, 104, 3, 177, 152, 71, 3, 74, 211, 104, 35, 240, 32, 3, 211, 96, 16, 189, 0, 191, 0, 16, 1, 64, 124, 1, 0, 32, 40, 1, 0, 32, 76, 1, 0, 32, 2, 75, 26, 104, 26, 104, 27, 104, 112, 71, 0, 191, 0, 68, 0, 64, 2, 75, 26, 104, 26, 104, 27, 104, 112, 71, 0, 191, 0, 20, 1, 64, 32, 244, 64, 115, 35, 240, 1, 3, 19, 187, 2, 241, 120, 67, 179, 245, 128, 47, 31, 210, 19, 75, 219, 104, 19, 244, 128, 63, 28, 209, 16, 180, 16, 76, 35, 105, 24, 67, 32, 97, 17, 96, 79, 244, 122, 115, 1, 224, 1, 59, 155, 178, 35, 177, 11, 74, 210, 104, 18, 244, 128, 63, 247, 209, 99, 177, 8, 74, 19, 105, 35, 240, 1, 3, 19, 97, 0, 32, 6, 224, 2, 32, 112, 71, 5, 32, 112, 71, 7, 32, 112, 71, 6, 32, 16, 188, 112, 71, 0, 191, 0, 60, 2, 64, 8, 181, 7, 75, 219, 104, 19, 240, 1, 15, 8, 208, 4, 74, 19, 105, 35, 240, 128, 115, 19, 97, 3, 75, 27, 104, 3, 177, 152, 71, 8, 189, 0, 60, 2, 64, 172, 1, 0, 32, 8, 181, 7, 72, 255, 247, 140, 251, 6, 75, 25, 120, 16, 41, 6, 209, 5, 74, 64, 242, 1, 32, 255, 247, 171, 255, 255, 247, 63, 254, 8, 189, 36, 25, 1, 8, 176, 1, 0, 32, 0, 64, 0, 8, 112, 181, 144, 176, 45, 72, 255, 247, 117, 251, 45, 76, 8, 173, 38, 70, 15, 206, 15, 197, 150, 232, 15, 0, 133, 232, 15, 0, 3, 173, 32, 52, 15, 204, 15, 197, 35, 104, 43, 96, 1, 32, 255, 247, 17, 254, 37, 72, 255, 247, 96, 251, 16, 32, 255, 247, 19, 254, 35, 72, 255, 247, 90, 251, 3, 168, 255, 247, 211, 252, 33, 72, 255, 247, 84, 251, 37, 32, 255, 247, 239, 253, 68, 32, 255, 247, 236, 253, 29, 72, 255, 247, 75, 251, 255, 247, 157, 253, 8, 168, 255, 247, 14, 254, 26, 72, 255, 247, 67, 251, 26, 72, 255, 247, 64, 251, 2, 35, 0, 147, 221, 233, 8, 35, 23, 72, 255, 247, 197, 254, 23, 72, 255, 247, 54, 251, 1, 34, 22, 73, 8, 168, 255, 247, 121, 254, 21, 72, 255, 247, 46, 251, 1, 33, 0, 32, 255, 247, 170, 253, 18, 72, 255, 247, 39, 251, 0, 33, 1, 32, 255, 247, 163, 253, 16, 72, 255, 247, 32, 251, 15, 72, 255, 247, 29, 251, 254, 231, 48, 25, 1, 8, 240, 24, 1, 8, 56, 25, 1, 8, 96, 25, 1, 8, 136, 25, 1, 8, 164, 25, 1, 8, 172, 25, 1, 8, 180, 25, 1, 8, 89, 13, 1, 8, 188, 25, 1, 8, 176, 1, 0, 32, 196, 25, 1, 8, 212, 25, 1, 8, 224, 25, 1, 8, 236, 25, 1, 8, 1, 75, 24, 104, 112, 71, 0, 191, 148, 0, 0, 32, 48, 181, 20, 30, 5, 70, 155, 176, 24, 70, 4, 218, 139, 35, 43, 96, 79, 240, 255, 48, 29, 224, 79, 244, 2, 115, 173, 248, 12, 48, 20, 191, 4, 241, 255, 51, 35, 70, 2, 147, 5, 147, 79, 246, 255, 115, 0, 145, 4, 145, 173, 248, 14, 48, 2, 70, 30, 155, 105, 70, 40, 70, 0, 240, 115, 248, 67, 28, 188, 191, 139, 35, 43, 96, 20, 177, 0, 155, 0, 34, 26, 112, 27, 176, 48, 189, 0, 0, 7, 181, 0, 147, 19, 70, 10, 70, 1, 70, 3, 72, 0, 104, 255, 247, 203, 255, 3, 176, 93, 248, 4, 251, 148, 0, 0, 32, 45, 233, 240, 71, 142, 104, 158, 66, 130, 70, 12, 70, 145, 70, 152, 70, 62, 216, 138, 137, 18, 244, 144, 111, 58, 208, 37, 104, 9, 105, 111, 26, 101, 105, 2, 35, 5, 235, 69, 5, 149, 251, 243, 245, 123, 28, 67, 68, 157, 66, 56, 191, 29, 70, 83, 5, 15, 213, 41, 70, 0, 240, 142, 251, 6, 70, 152, 177, 58, 70, 33, 105, 0, 240, 20, 251, 163, 137, 35, 244, 144, 99, 67, 240, 128, 3, 163, 129, 19, 224, 42, 70, 0, 240, 220, 251, 6, 70, 112, 185, 33, 105, 80, 70, 0, 240, 42, 251, 12, 35, 202, 248, 0, 48, 163, 137, 67, 240, 64, 3, 163, 129, 79, 240, 255, 48, 189, 232, 240, 135, 38, 97, 101, 97, 62, 68, 237, 27, 38, 96, 165, 96, 70, 70, 70, 69, 40, 191, 70, 70, 50, 70, 73, 70, 32, 104, 0, 240, 245, 250, 163, 104, 155, 27, 163, 96, 35, 104, 30, 68, 38, 96, 0, 32, 189, 232, 240, 135, 0, 0, 45, 233, 240, 79, 157, 176, 128, 70, 3, 147, 139, 137, 28, 6, 13, 70, 22, 70, 13, 213, 11, 105, 91, 185, 64, 33, 0, 240, 69, 251, 40, 96, 40, 97, 24, 185, 12, 35, 200, 248, 0, 48, 205, 224, 64, 35, 107, 97, 0, 35, 9, 147, 32, 35, 141, 248, 41, 48, 223, 248, 156, 177, 48, 35, 141, 248, 42, 48, 55, 70, 60, 70, 20, 248, 1, 59, 27, 185, 183, 235, 6, 9, 16, 208, 3, 224, 37, 43, 249, 208, 39, 70, 243, 231, 75, 70, 50, 70, 41, 70, 64, 70, 255, 247, 113, 255, 1, 48, 0, 240, 167, 128, 9, 155, 75, 68, 9, 147, 59, 120, 0, 43, 0, 240, 160, 128, 0, 35, 79, 240, 255, 50, 4, 147, 7, 147, 5, 146, 6, 147, 141, 248, 83, 48, 26, 147, 1, 38, 5, 34, 33, 120, 78, 72, 0, 240, 65, 250, 103, 28, 4, 155, 56, 177, 75, 74, 128, 26, 6, 250, 0, 240, 24, 67, 4, 144, 60, 70, 239, 231, 217, 6, 68, 191, 32, 34, 141, 248, 83, 32, 26, 7, 68, 191, 43, 34, 141, 248, 83, 32, 34, 120, 42, 42, 3, 208, 7, 154, 0, 33, 10, 32, 11, 224, 3, 154, 17, 29, 18, 104, 3, 145, 0, 42, 16, 218, 82, 66, 67, 240, 2, 0, 7, 146, 4, 144, 11, 224, 39, 70, 1, 52, 59, 120, 48, 59, 9, 43, 3, 216, 0, 251, 2, 50, 1, 33, 245, 231, 1, 177, 7, 146, 59, 120, 46, 43, 30, 209, 123, 120, 42, 43, 10, 209, 3, 155, 26, 29, 27, 104, 3, 146, 0, 43, 184, 191, 79, 240, 255, 51, 2, 55, 5, 147, 16, 224, 0, 35, 5, 147, 120, 28, 25, 70, 10, 36, 7, 70, 1, 48, 58, 120, 48, 58, 9, 42, 3, 216, 4, 251, 1, 33, 1, 35, 245, 231, 3, 177, 5, 145, 3, 34, 57, 120, 34, 72, 0, 240, 230, 249, 64, 177, 64, 35, 203, 235, 0, 0, 3, 250, 0, 240, 4, 155, 24, 67, 4, 144, 1, 55, 57, 120, 28, 72, 141, 248, 40, 16, 6, 34, 126, 28, 0, 240, 212, 249, 136, 177, 25, 75, 51, 185, 3, 155, 7, 51, 35, 240, 7, 3, 8, 51, 3, 147, 20, 224, 3, 171, 0, 147, 42, 70, 20, 75, 4, 169, 64, 70, 175, 243, 0, 128, 7, 224, 3, 171, 0, 147, 42, 70, 15, 75, 4, 169, 64, 70, 0, 240, 147, 248, 176, 241, 255, 63, 130, 70, 3, 208, 9, 155, 83, 68, 9, 147, 66, 231, 171, 137, 91, 6, 1, 212, 9, 152, 1, 224, 79, 240, 255, 48, 29, 176, 189, 232, 240, 143, 0, 191, 252, 25, 1, 8, 2, 26, 1, 8, 6, 26, 1, 8, 0, 0, 0, 0, 253, 14, 1, 8, 45, 233, 240, 71, 145, 70, 31, 70, 10, 105, 139, 104, 221, 248, 32, 128, 147, 66, 184, 191, 19, 70, 201, 248, 0, 48, 145, 248, 67, 32, 6, 70, 12, 70, 18, 177, 1, 51, 201, 248, 0, 48, 35, 104, 153, 6, 66, 191, 217, 248, 0, 48, 2, 51, 201, 248, 0, 48, 37, 104, 21, 240, 6, 5, 16, 209, 4, 241, 25, 10, 7, 224, 1, 35, 82, 70, 57, 70, 48, 70, 192, 71, 1, 48, 26, 208, 1, 53, 227, 104, 217, 248, 0, 32, 155, 26, 157, 66, 241, 219, 148, 248, 67, 48, 34, 104, 0, 51, 24, 191, 1, 35, 146, 6, 15, 213, 225, 24, 90, 28, 48, 32, 129, 248, 67, 0, 34, 68, 148, 248, 69, 16, 130, 248, 67, 16, 2, 51, 3, 224, 79, 240, 255, 48, 189, 232, 240, 135, 4, 241, 67, 2, 57, 70, 48, 70, 192, 71, 1, 48, 244, 208, 34, 104, 217, 248, 0, 80, 227, 104, 2, 240, 6, 2, 4, 42, 8, 191, 93, 27, 34, 105, 163, 104, 12, 191, 37, 234, 229, 117, 0, 37, 147, 66, 196, 191, 155, 26, 237, 24, 79, 240, 0, 9, 26, 52, 77, 69, 9, 208, 1, 35, 34, 70, 57, 70, 48, 70, 192, 71, 1, 48, 213, 208, 9, 241, 1, 9, 243, 231, 0, 32, 189, 232, 240, 135, 45, 233, 240, 67, 23, 70, 10, 126, 133, 176, 110, 42, 152, 70, 6, 70, 12, 70, 12, 155, 1, 241, 67, 14, 0, 240, 174, 128, 17, 216, 99, 42, 34, 208, 9, 216, 0, 42, 0, 240, 187, 128, 88, 42, 64, 240, 202, 128, 129, 248, 69, 32, 131, 73, 85, 224, 100, 42, 30, 208, 105, 42, 28, 208, 192, 224, 115, 42, 0, 240, 176, 128, 9, 216, 111, 42, 46, 208, 112, 42, 64, 240, 184, 128, 10, 104, 66, 240, 32, 2, 10, 96, 62, 224, 117, 42, 36, 208, 120, 42, 58, 208, 173, 224, 26, 104, 1, 241, 66, 5, 17, 29, 25, 96, 19, 104, 132, 248, 66, 48, 168, 224, 33, 104, 26, 104, 17, 240, 128, 15, 2, 208, 17, 29, 25, 96, 8, 224, 17, 240, 64, 15, 2, 241, 4, 1, 25, 96, 2, 208, 178, 249, 0, 48, 0, 224, 19, 104, 0, 43, 60, 218, 45, 34, 91, 66, 132, 248, 67, 32, 55, 224, 33, 104, 26, 104, 17, 240, 128, 15, 2, 208, 17, 29, 25, 96, 7, 224, 17, 240, 64, 15, 2, 241, 4, 1, 25, 96, 1, 208, 19, 136, 0, 224, 19, 104, 34, 126, 92, 73, 111, 42, 20, 191, 10, 34, 8, 34, 27, 224, 120, 34, 90, 73, 132, 248, 69, 32, 34, 104, 24, 104, 18, 240, 128, 15, 0, 241, 4, 5, 29, 96, 3, 209, 85, 6, 1, 213, 3, 136, 0, 224, 3, 104, 208, 7, 68, 191, 66, 240, 32, 2, 34, 96, 27, 185, 34, 104, 34, 240, 32, 2, 34, 96, 16, 34, 0, 32, 132, 248, 67, 0, 1, 224, 73, 73, 10, 34, 101, 104, 165, 96, 0, 45, 8, 219, 32, 104, 32, 240, 4, 0, 32, 96, 43, 185, 0, 45, 125, 209, 117, 70, 12, 224, 0, 43, 121, 208, 117, 70, 179, 251, 242, 240, 2, 251, 16, 51, 203, 92, 5, 248, 1, 61, 3, 70, 0, 40, 245, 209, 8, 42, 11, 209, 35, 104, 218, 7, 8, 213, 35, 105, 98, 104, 154, 66, 222, 191, 48, 35, 5, 248, 1, 60, 5, 241, 255, 53, 197, 235, 14, 3, 35, 97, 46, 224, 8, 104, 26, 104, 73, 105, 16, 240, 128, 15, 3, 208, 16, 29, 24, 96, 19, 104, 8, 224, 16, 240, 64, 15, 2, 241, 4, 0, 24, 96, 19, 104, 1, 208, 25, 128, 0, 224, 25, 96, 0, 35, 35, 97, 117, 70, 22, 224, 26, 104, 17, 29, 25, 96, 21, 104, 98, 104, 0, 33, 40, 70, 0, 240, 73, 248, 8, 177, 64, 27, 96, 96, 99, 104, 4, 224, 4, 241, 66, 5, 132, 248, 66, 32, 1, 35, 35, 97, 0, 35, 132, 248, 67, 48, 205, 248, 0, 128, 59, 70, 3, 170, 33, 70, 48, 70, 255, 247, 151, 254, 1, 48, 2, 209, 79, 240, 255, 48, 38, 224, 35, 105, 42, 70, 57, 70, 48, 70, 192, 71, 1, 48, 245, 208, 35, 104, 155, 7, 16, 213, 0, 37, 4, 241, 25, 9, 7, 224, 1, 35, 74, 70, 57, 70, 48, 70, 192, 71, 1, 48, 231, 208, 1, 53, 227, 104, 3, 154, 155, 26, 157, 66, 242, 219, 224, 104, 3, 155, 152, 66, 184, 191, 24, 70, 5, 224, 11, 120, 132, 248, 66, 48, 4, 241, 66, 5, 138, 231, 5, 176, 189, 232, 240, 131, 13, 26, 1, 8, 30, 26, 1, 8, 1, 240, 255, 1, 16, 42, 43, 219, 16, 240, 7, 15, 8, 208, 16, 248, 1, 59, 1, 58, 139, 66, 45, 208, 16, 240, 7, 15, 66, 179, 246, 209, 240, 180, 65, 234, 1, 33, 65, 234, 1, 65, 34, 240, 7, 4, 127, 240, 0, 7, 0, 35, 240, 232, 2, 86, 8, 60, 133, 234, 1, 5, 134, 234, 1, 6, 133, 250, 71, 245, 163, 250, 135, 245, 134, 250, 71, 246, 165, 250, 135, 246, 142, 185, 238, 209, 240, 188, 1, 240, 255, 1, 2, 240, 7, 2, 50, 177, 16, 248, 1, 59, 1, 58, 131, 234, 1, 3, 19, 177, 248, 209, 0, 32, 112, 71, 1, 56, 112, 71, 0, 45, 6, 191, 53, 70, 3, 56, 7, 56, 21, 240, 1, 15, 7, 209, 1, 48, 21, 244, 128, 127, 2, 191, 1, 48, 21, 244, 192, 63, 1, 48, 240, 188, 1, 56, 112, 71, 0, 191, 16, 181, 67, 30, 10, 68, 145, 66, 4, 208, 17, 248, 1, 75, 3, 248, 1, 79, 248, 231, 16, 189, 136, 66, 16, 181, 1, 235, 2, 3, 1, 216, 66, 30, 11, 224, 152, 66, 251, 210, 129, 24, 210, 26, 211, 66, 4, 208, 19, 248, 1, 77, 1, 248, 1, 77, 248, 231, 16, 189, 153, 66, 4, 208, 17, 248, 1, 75, 2, 248, 1, 79, 248, 231, 16, 189, 56, 181, 5, 70, 0, 41, 70, 208, 81, 248, 4, 60, 12, 31, 0, 43, 184, 191, 228, 24, 0, 240, 214, 248, 31, 74, 19, 104, 17, 70, 19, 185, 99, 96, 20, 96, 50, 224, 163, 66, 14, 217, 34, 104, 160, 24, 131, 66, 4, 191, 24, 104, 91, 104, 99, 96, 4, 191, 18, 24, 34, 96, 12, 96, 36, 224, 162, 66, 3, 216, 19, 70, 90, 104, 0, 42, 249, 209, 24, 104, 25, 24, 161, 66, 11, 209, 33, 104, 1, 68, 88, 24, 130, 66, 25, 96, 20, 209, 16, 104, 82, 104, 90, 96, 1, 68, 25, 96, 14, 224, 2, 217, 12, 35, 43, 96, 10, 224, 33, 104, 96, 24, 130, 66, 4, 191, 16, 104, 82, 104, 98, 96, 4, 191, 9, 24, 33, 96, 92, 96, 40, 70, 189, 232, 56, 64, 0, 240, 152, 184, 56, 189, 184, 1, 0, 32, 112, 181, 205, 28, 37, 240, 3, 5, 8, 53, 12, 45, 56, 191, 12, 37, 0, 45, 6, 70, 1, 219, 169, 66, 2, 217, 12, 35, 51, 96, 70, 224, 0, 240, 130, 248, 35, 75, 28, 104, 26, 70, 33, 70, 161, 177, 11, 104, 91, 27, 14, 212, 11, 43, 3, 217, 11, 96, 204, 24, 205, 80, 30, 224, 140, 66, 13, 191, 99, 104, 75, 104, 99, 96, 19, 96, 24, 191, 12, 70, 21, 224, 12, 70, 73, 104, 233, 231, 23, 76, 35, 104, 27, 185, 48, 70, 0, 240, 82, 248, 32, 96, 41, 70, 48, 70, 0, 240, 77, 248, 67, 28, 24, 208, 196, 28, 36, 240, 3, 4, 160, 66, 13, 209, 37, 96, 48, 70, 0, 240, 83, 248, 4, 241, 11, 0, 35, 29, 32, 240, 7, 0, 195, 26, 14, 208, 90, 66, 226, 80, 112, 189, 33, 26, 48, 70, 0, 240, 52, 248, 1, 48, 235, 209, 12, 35, 51, 96, 48, 70, 0, 240, 62, 248, 0, 32, 112, 189, 0, 191, 184, 1, 0, 32, 180, 1, 0, 32, 248, 181, 7, 70, 21, 70, 14, 70, 33, 185, 17, 70, 189, 232, 248, 64, 255, 247, 152, 191, 26, 185, 255, 247, 71, 255, 40, 70, 248, 189, 0, 240, 39, 248, 133, 66, 14, 217, 41, 70, 56, 70, 255, 247, 139, 255, 4, 70, 80, 177, 49, 70, 42, 70, 255, 247, 17, 255, 49, 70, 56, 70, 255, 247, 51, 255, 1, 224, 48, 70, 248, 189, 32, 70, 248, 189, 56, 181, 6, 76, 0, 35, 5, 70, 8, 70, 35, 96, 254, 247, 90, 254, 67, 28, 2, 209, 35, 104, 3, 177, 43, 96, 56, 189, 188, 1, 0, 32, 112, 71, 112, 71, 81, 248, 4, 12, 0, 40, 190, 191, 9, 24, 81, 248, 4, 60, 192, 24, 4, 56, 112, 71, 83, 116, 97, 99, 107, 32, 102, 114, 97, 109, 101, 58, 10, 0, 0, 0, 32, 82, 48, 32, 61, 32, 32, 37, 48, 56, 88, 10, 0, 0, 0, 0, 32, 82, 49, 32, 61, 32, 32, 37, 48, 56, 88, 10, 0, 0, 0, 0, 32, 82, 50, 32, 61, 32, 32, 37, 48, 56, 88, 10, 0, 0, 0, 0, 32, 82, 51, 32, 61, 32, 32, 37, 48, 56, 88, 10, 0, 0, 0, 0, 32, 82, 49, 50, 32, 61, 32, 37, 48, 56, 88, 10, 0, 0, 0, 0, 32, 76, 82, 32, 61, 32, 32, 37, 48, 56, 88, 10, 0, 0, 0, 0, 32, 80, 67, 32, 61, 32, 32, 37, 48, 56, 88, 10, 0, 0, 0, 0, 32, 80, 83, 82, 32, 61, 32, 37, 48, 56, 88, 10, 0, 0, 0, 0, 70, 83, 82, 47, 70, 65, 82, 58, 10, 0, 0, 0, 32, 67, 70, 83, 82, 32, 61, 32, 32, 37, 48, 56, 88, 10, 0, 0, 32, 72, 70, 83, 82, 32, 61, 32, 32, 37, 48, 56, 88, 10, 0, 0, 32, 68, 70, 83, 82, 32, 61, 32, 32, 37, 48, 56, 88, 10, 0, 0, 32, 65, 70, 83, 82, 32, 61, 32, 32, 37, 48, 56, 88, 10, 0, 0, 32, 77, 77, 70, 65, 82, 32, 61, 32, 37, 48, 56, 88, 10, 0, 0, 32, 66, 70, 65, 82, 32, 61, 32, 32, 37, 48, 56, 88, 10, 0, 0, 77, 105, 115, 99, 10, 0, 0, 0, 32, 76, 82, 47, 69, 88, 67, 95, 82, 69, 84, 85, 82, 78, 61, 32, 37, 48, 56, 88, 10, 0, 0, 0, 91, 72, 97, 114, 100, 70, 97, 117, 108, 116, 93, 10, 0, 0, 0, 0, 91, 66, 117, 115, 70, 97, 117, 108, 116, 93, 10, 0, 91, 85, 115, 97, 103, 101, 70, 97, 117, 108, 116, 93, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9, 0, 16, 1, 64, 0, 0, 0, 0, 130, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 64, 0, 6, 0, 128, 7, 0, 0, 192, 0, 0, 2, 64, 69, 110, 116, 101, 114, 32, 67, 112, 102, 10, 0, 0, 65, 110, 97, 32, 101, 108, 10, 0, 82, 99, 99, 95, 65, 72, 66, 49, 95, 80, 101, 114, 105, 112, 104, 101, 114, 97, 108, 69, 110, 97, 98, 108, 101, 40, 82, 67, 67, 95, 71, 80, 73, 79, 65, 41, 59, 10, 0, 0, 82, 99, 99, 95, 65, 80, 66, 50, 95, 80, 101, 114, 105, 112, 104, 101, 114, 97, 108, 69, 110, 97, 98, 108, 101, 40, 82, 67, 67, 95, 85, 83, 65, 82, 84, 49, 41, 59, 10, 0, 103, 112, 105, 111, 73, 110, 105, 116, 80, 111, 114, 116, 40, 38, 71, 112, 105, 111, 95, 73, 110, 105, 116, 10, 0, 0, 0, 0, 110, 118, 105, 99, 10, 0, 0, 0, 85, 65, 82, 84, 10, 0, 0, 0, 70, 108, 97, 115, 104, 10, 0, 0, 67, 80, 70, 10, 0, 0, 0, 0, 85, 65, 82, 84, 73, 110, 116, 101, 114, 114, 117, 112, 116, 10, 0, 0, 76, 101, 100, 83, 116, 97, 114, 116, 10, 0, 0, 0, 76, 101, 100, 83, 116, 111, 112, 10, 0, 0, 0, 0, 69, 110, 116, 101, 114, 87, 104, 105, 108, 101, 108, 111, 111, 112, 10, 0, 35, 45, 48, 43, 32, 0, 104, 108, 76, 0, 101, 102, 103, 69, 70, 71, 0, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70, 0, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 97, 98, 99, 100, 101, 102, 0, 255, 120, 86, 52, 18, 164, 0, 0, 32, 0, 0, 0, 0, 0, 36, 244, 0, 0, 0, 2, 64, 1, 0, 0, 128, 0, 0, 0, 0, 0, 0, 2, 64, 2, 0, 0, 128, 1, 0, 0, 0, 0, 0, 2, 64, 4, 0, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 52, 0, 0, 32, 50, 84, 118, 152};

void notification(void);


int main (void)
{
	BootLoaderInit();
	FlashUnlock();
	FlashErase(FLASH_SECTOR1);

	while(1)
	{

		BootLoaderFlashingSeq();
	}
}

//int main(void)
//{
//	static u32 counter;
//	FlashUnlock();
//	FlashErase(FLASH_SECTOR1);
//	for(counter = 0 ; counter <= 1715; counter+=4)
//	{
//		u32* ptr=(u32*)(arr+counter);
//		FlashProgram(PARALLELISM_SIZE_32,*(ptr),0x08004000+counter);
//	}
//
////	Usart_vidHalInit();
////	Usart_enuRegRxCompNotifyCbf(notification,Usart_enuBusNum1);
//////  while (1)
//////    {
////	    Usart_enuRecieveBufferSync(arr1,11,Usart_enuBusNum1);
//////    }
//	  while (1);
//}
//
//void notification(void)
//{
//	trace_printf("%s",arr1);
//}


