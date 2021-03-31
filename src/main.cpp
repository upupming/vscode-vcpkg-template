#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <sqlite3.h>

#include <iostream>
#include <string>

bool getInfo(DcmFileFormat& fileformat, const DcmTagKey& tagKey, std::string& info) {
    OFString ofData;
    OFCondition status = fileformat.getDataset()->findAndGetOFString(tagKey, ofData);
    if (status.bad()) {
        std::cout << "get tag " << tagKey.toString() << DcmTag(tagKey).getTagName() << "error: " << status.text();
        return false;
    }
    info = ofData.c_str();
    return true;
}

int main() {
    // --- Test DCMTK (Static Linking)
    TCHAR NPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, NPath);
    std::cout << "Current work directory: " << NPath << std::endl;
    std::string dcmFile = (std::string(NPath) + "\\build\\assets\\0002.DCM");
    std::cout << dcmFile << std::endl;

    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(dcmFile.c_str());
    if (status.bad()) {
        std::cerr << std::string("Error: cannot read DICOM file: ") + status.text() << std::endl;
        return 1;
    }

    std::string numOfFrames;
    if (!getInfo(fileformat, DCM_NumberOfFrames, numOfFrames)) return 1;
    std::cout << "numOfFrames of DCM file: " << numOfFrames << std::endl;

    // --- Test SQLite3 (Copy DLLs)
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
    sqlite3_close(db);
    return 0;
}
