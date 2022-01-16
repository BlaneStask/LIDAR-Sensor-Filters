#include <iostream>
using namespace std;

class range_filter {
    private:
        float range_min = 0.03;
        float range_max = 50.0;

        /** 
         * This method is used to get Range filters from the given array of length-N
         *
         * @param  scan   input array
         * @param  N      input array length
         * @return scan   range filtered scan
         */
        float* update(float scan[], const int N) {
            for (int i = 0; i < N; i++) {
                // replace smallest values with min value
                if (scan[i] < range_min) {
                    scan[i] = range_min;
                }
                // replace largest values with max value
                else if (scan[i] > range_max) {
                    scan[i] = range_max;
                }
            }
            return scan;
        }
};

class temp_m_filter {
    public:
        /** 
         * This method is used to get Temporal median filters from the given array of length-N 
         *
         * @param  new_scan    input array
         * @param  N           input array length
         * @param  T           total number of times to update (T < 6)
         * @param  count       current updated filter (count <= T)
         *                     determines how to get new median filter values
         * @param  arr0        previous output scan
         * @param  arr1        previous output scan
         * @param  arr2        previous output scan
         * @param  arr3        previous output scan
         * @param  arr4        previous output scan
         * @param  scan1       input scan 
         * @param  scan2       input scan
         * @param  scan3       input scan
         * @return  arr        temporal median filtered scan
         */
        float* update(float new_scan[], const int N, const int T, int count, float arr0[], float arr1[],
                      float arr2[], float arr3[], float arr4[], float scan1[], float scan2[], float scan3[]) {
            // first scan just returns itself
            if (count == 0) {
                for (int i = 0; i < N; i++) {
                    arr0[i] = new_scan[i];
                }
                return new_scan;
            }
            // with two scans, can add values and divide by 2 to get median
            else if (count == 1) {
                for (int i = 0; i < N; i++) {
                    arr1[i] += (new_scan[i] + arr0[i])/2;
                    scan1[i] += new_scan[i];
                }
                return arr1;
            }
            // even value, find middle value (not smallest and not largest of the 3)
            else if (count % 2 == 0) {
                for (int i = 0; i < N; i++) {
                    if ((new_scan[i] >= scan1[i] && new_scan[i] <= arr0[i]) ||
                       (new_scan[i] <= scan1[i] && new_scan[i] >= arr0[i])) {
                        arr2[i] += new_scan[i];
                    }
                    else if ((scan1[i] >= new_scan[i] && scan1[i] <= arr0[i]) ||
                       (scan1[i] <= new_scan[i] && scan1[i] >= arr0[i])) {
                        arr2[i] += scan1[i];
                    }
                    else {
                        arr2[i] += arr0[i];
                    }
                    scan2[i] += new_scan[i];
                }
                return arr2;
            }
            // odd value, find largest and smallest value and disguard, add 2 middle and divide by 2
            else if (count % 2 != 0) {
                for (int i = 0; i < N; i++) {
                    // new_scan largest
                    if (new_scan[i] >= scan2[i] && new_scan[i] >= scan1[i] && new_scan[i] >= arr0[i]) {
                        // arr0 is smallest
                        if (arr0[i] <= scan1[i] && arr0[i] <= scan2[i] && arr0[i] <= new_scan[i]) {
                            arr3[i] += (scan2[i] + scan1[i])/2;
                        }
                        // arr1 is smallest
                        else if (scan1[i] <= arr0[i] && scan1[i] <= scan2[i] && scan1[i] <= new_scan[i]) {
                            arr3[i] += (scan2[i] + arr0[i])/2;
                        }
                        // arr2 is smallest
                        else {
                            arr3[i] += (scan1[i] + arr0[i])/2;
                        }
                    }
                    // arr0 is largest
                    else if (arr0[i] >= scan2[i] && arr0[i] >= scan1[i] && arr0[i] >= new_scan[i]) {
                        // new_scan is smallest
                        if (new_scan[i] <= scan1[i] && new_scan[i] <= scan2[i] && new_scan[i] <= arr0[i]) {
                            arr3[i] += (scan2[i] + scan1[i])/2;
                        }
                        // arr1 is smallest
                        else if (scan1[i] <= arr0[i] && scan1[i] <= scan2[i] && scan1[i] <= new_scan[i]) {
                            arr3[i] += (scan2[i] + arr0[i])/2;
                        }
                        // arr2 is smallest
                        else {
                            arr3[i] += (scan1[i] + new_scan[i])/2;
                        }
                    }
                    // arr1 is largest
                    else if (scan1[i] >= scan2[i] && scan1[i] >= new_scan[i] && scan1[i] >= arr0[i]) {
                        // arr0 is smallest
                        if (arr0[i] <= scan1[i] && arr0[i] <= scan2[i] && arr0[i] <= new_scan[i]) {
                            arr3[i] += (scan2[i] + new_scan[i])/2;
                        }
                        // arr2 is smallest
                        else if (scan2[i] <= arr0[i] && scan2[i] <= scan1[i] && scan2[i] <= new_scan[i]) {
                            arr3[i] += (new_scan[i] + arr0[i])/2;
                        }
                        // new_scan is smallest
                        else {
                            arr3[i] += (scan2[i] + arr0[i])/2;
                        }
                    }
                    // arr2 is largest
                    else {
                        //arr0 is smallest
                        if (arr0[i] <= scan1[i] && arr0[i] <= scan2[i] && arr0[i] <= new_scan[i]) {
                            arr3[i] += (new_scan[i] + scan1[i])/2;
                        }
                        // arr1 is smallest
                        else if (scan1[i] <= arr0[i] && scan1[i] <= scan2[i] && scan1[i] <= new_scan[i]) {
                            arr3[i] += (new_scan[i] + arr0[i])/2;
                        }
                        // new_scan is smallest
                        else {
                            arr3[i] += (scan1[i] + arr0[i])/2;
                        }
                    }
                    scan3[i] += new_scan[i];
                }
                return arr3;
            }
            // not expected to return here
            return arr0;
        }
};

/** 
 * This function is used to output the new temporal medium filtered scan
 *
 * @param  new_scan    input array
 * @param  N           input array length
 * @param  T           total number of times to update (T < 6)
 * @param  count       current updated filter (count <= T)
 *                     determines how to get new median filter values
 * @param  arr0        previous output scan
 * @param  arr1        previous output scan
 * @param  arr2        previous output scan
 * @param  arr3        previous output scan
 * @param  arr4        previous output scan
 * @param  scan1       input scan 
 * @param  scan2       input scan
 * @param  scan3       input scan
 */
int temp_filter(float* new_scan, const int N, const int T, int count, float arr0[], float arr1[], 
                float arr2[], float arr3[], float arr4[], float scan1[], float scan2[], float scan3[]) {
    temp_m_filter object_;
    float *new_scan_ = object_.update(new_scan, N, T, count, arr0, arr1, arr2, arr3, arr4, scan1, scan2, scan3);
    
    // output new temporal medium filtered scan
    cout << "[";
    for (int i = 0; i < N; i++) {
        if (i < N - 1) {
            cout << new_scan_[i] << ", ";
        }
        else {
            cout << new_scan_[i];
        }
    }
    cout << "]" << endl;
    return 0;
}

/**
 * <h1>LIDAR Sensor Filters</h1>
 * This program reduces the noise in the data coming from
 * a LIDAR sensor attached to a robot.
 *
 * This function is the Driver function, gets inputs and
 * calls Range update and temp_filter
 *
 * @author  Blane Staskiewicz
 */
int main() {
    int N = 0;
    int T = 0;
    int count = 0;

    cout << "Give the value for T (Times updated, less than 6): " << endl;
    cin >> T;
    cout << "The length of each Scan: " << endl;
    cin >> N;
    
    // allocate memory arrays of length-N (output scans)
    float* arr1 = new float[N];
    float* arr2 = new float[N];
    float* arr3 = new float[N];
    float* arr4 = new float[N];
    
    // allocate memory for arrays of length-N
    float* arr0 = new float[N];
    float* scan1 = new float[N];
    float* scan2 = new float[N];
    float* scan3 = new float[N];
    
    // valid measurements check
    if (N > 1000) {
        cout << "Invalid range measurements (max: 1000)." << endl;
        return 0;
    }
    else if (N < 200) {
        cout << "Invalid range measurements (min: 200)." << endl;
        return 0;
    }

    // based on how many times the scans are updated
    for (int i = 0; i < T; i++) {
        float scan[N];
        for (int i = 0; i < N; i++) {
            cout << "Array values from the scan: " << endl;
            cin >> scan[i];
        }
        
        range_filter object;
        float *new_scan = object.update(scan, N);
        
        // output new range filtered scan
        cout << "The Scan after the Range Filter is: " << endl;
        cout << "[";
        for (int i = 0; i < N; i++) {
            if (i < N-1) {
                cout << new_scan[i] << ", ";
            }
            else {
                cout << new_scan[i];
            }
        }
        cout << "]" << endl;
        cout << "The Scan after the Temporal Median Filter is: " << endl;
        temp_filter(new_scan, N, T, count, arr0, arr1, arr2, arr3, arr4, scan1, scan2, scan3);
        
        if (count < T) {
            count++;
        }
    }
    return 0;
}
