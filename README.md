# LIDAR Sensor Scan Filters

This program reduces noise in the data coming from a LIDAR sensor attached to a robot. It filters the scans into a Range and a Temporal Median filter.


## Example

Here is an example of scans of size 20:

```
Give the value for T (Times updated, less than 6): 
4
The length of each Scan: 
20
Array values from the scan: 
-20
Array values from the scan: 
4
Array values from the scan: 
156
Array values from the scan: 
23
Array values from the scan: 
34
Array values from the scan: 
74
Array values from the scan: 
13
Array values from the scan: 
6
Array values from the scan: 
29
Array values from the scan: 
43
Array values from the scan: 
82
Array values from the scan: 
27
Array values from the scan: 
42
Array values from the scan: 
5
Array values from the scan: 
9
Array values from the scan: 
18
Array values from the scan: 
21
Array values from the scan: 
62
Array values from the scan: 
53
Array values from the scan: 
96
The Scan after the Range Filter is: 
[0.03, 4, 50, 23, 34, 50, 13, 6, 29, 43, 50, 27, 42, 5, 9, 18, 21, 50, 50, 50]
The Scan after the Temporal Median Filter is: 
[0.03, 4, 50, 23, 34, 50, 13, 6, 29, 43, 50, 27, 42, 5, 9, 18, 21, 50, 50, 50]
Array values from the scan: 
3
Array values from the scan: 
1
Array values from the scan: 
2
Array values from the scan: 
86
Array values from the scan: 
32
Array values from the scan: 
48
Array values from the scan: 
62
Array values from the scan: 
36
Array values from the scan: 
51
Array values from the scan: 
48
Array values from the scan: 
74
Array values from the scan: 
98
Array values from the scan: 
35
Array values from the scan: 
72
Array values from the scan: 
30
Array values from the scan: 
65
Array values from the scan: 
45
Array values from the scan: 
23
Array values from the scan: 
43
Array values from the scan: 
12
The Scan after the Range Filter is: 
[3, 1, 2, 50, 32, 48, 50, 36, 50, 48, 50, 50, 35, 50, 30, 50, 45, 23, 43, 12]
The Scan after the Temporal Median Filter is: 
[1.515, 2.5, 26, 36.5, 33, 49, 31.5, 21, 39.5, 45.5, 50, 38.5, 38.5, 27.5, 19.5, 34, 33, 36.5, 46.5, 31]
Array values from the scan: 
38
Array values from the scan: 
52
Array values from the scan: 
36
Array values from the scan: 
96
Array values from the scan: 
14
Array values from the scan: 
72
Array values from the scan: 
39
Array values from the scan: 
52
Array values from the scan: 
43
Array values from the scan: 
61
Array values from the scan: 
91
Array values from the scan: 
13
Array values from the scan: 
42
Array values from the scan: 
17
Array values from the scan: 
-12
Array values from the scan: 
0
Array values from the scan: 
17
Array values from the scan: 
-32
Array values from the scan: 
16
Array values from the scan: 
28
The Scan after the Range Filter is: 
[38, 50, 36, 50, 14, 50, 39, 50, 43, 50, 50, 13, 42, 17, 0.03, 0.03, 17, 0.03, 16, 28]
The Scan after the Temporal Median Filter is: 
[3, 4, 36, 50, 32, 50, 39, 36, 43, 48, 50, 27, 42, 17, 9, 18, 21, 23, 43, 28]
Array values from the scan: 
5
Array values from the scan: 
1
Array values from the scan: 
8
Array values from the scan: 
14
Array values from the scan: 
456
Array values from the scan: 
23
Array values from the scan: 
95
Array values from the scan: 
23
Array values from the scan: 
643
Array values from the scan: 
81
Array values from the scan: 
16
Array values from the scan: 
134
Array values from the scan: 
73
Array values from the scan: 
43
Array values from the scan: 
-12
Array values from the scan: 
54
Array values from the scan: 
13
Array values from the scan: 
73
Array values from the scan: 
15
Array values from the scan: 
92
The Scan after the Range Filter is: 
[5, 1, 8, 14, 50, 23, 50, 23, 50, 50, 16, 50, 50, 43, 0.03, 50, 13, 50, 15, 50]
The Scan after the Temporal Median Filter is: 
[4, 2.5, 43, 36.5, 33, 49, 44.5, 29.5, 46.5, 49, 50, 38.5, 42, 30, 4.515, 34, 19, 36.5, 29.5, 39]
```
