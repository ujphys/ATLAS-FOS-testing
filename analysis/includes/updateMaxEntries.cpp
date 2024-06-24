double updateMaxEntries(TH1D* hist, double current_max)
{
    /*Get the maximum entries from a histogram
    Compare to the current max entries and return the larger value*/
    int maxBin = hist->GetMaximumBin();
    double maxEntries = hist->GetBinContent(maxBin);
    cout << "Current_max: " << current_max << endl;
    cout << "maxEntries: " << maxEntries << endl;
    if (maxEntries > current_max){ current_max = maxEntries; }
    return current_max;
}