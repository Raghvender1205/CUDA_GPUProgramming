#ifndef IMAGE_RW_CUDA_H
#define IMAGE_RW_CUDA_H


/// Include files for libtiff, libjpeg, libpng
#include <tiffio.h>
#include <jpeglib.h>
#include <png.h>

#include "image_rw_cuda_fwd.h"

/// Enumerate to select the pointers of an image
enum imagePointerNo {
    RGB_DATA,
    Y_COMPONENT,
    CONVERTED_DATA
};

///
/// The enumeration for using pageable/page-locked(pnned memory) 
/// If all the computation is performed on a GPU, page-locked memory
/// should be used to shorten the data transfer time between a GPU
/// and a CPU.
/// Note that the use of pinned memory often makes CPU execution
/// much slower.
enum hostMemoryType {
    PAGEABLE_MEMORY,
    PAGE_LOCKED_MEMORY
};

/// Seperate Array image class on a device
template <typename T>
class dsaImage {
    private:
        // image channels
        static const unsigned int RGB = 3;

        // Image sizes and pointers
        unsigned int mWidth;
        unsigned int mHeight
        T *mData[RGB];

        //
        // A color converted image
        // Note that every conversion is performed on a GPU 
        // Data space is allocated when the image is transfered to a GPU
        //
        T *mYComp;          // Y Component image i.e BW image
        T *mConvData[RGB];  // Converted data such as YUV, default RGB
    
    public:
        dsaImage();
        ~dsaImage();

        /// Inline Function for getters

        /** Get Image Width and Height  */
        unsigned int getImageWidth() { return mWidth; }
        unsigned int getImageHeight() { return mHeight; }

        /** Get Pointers */
        T *getImagePtr( const unsigned int &channel_no) { return mData[channel_no]; }
        T *getYCompPtr() { return mYComp; }
        T *getConvImagePtr( const unsigned int &channel_no ) { return mConvData[channel_no]; }

        //
        // Member functions for memory allocation and free
        // The size of an image should be obtained by GetImageSize() of each image type or given by arguments.
        //
        int allocImage();
        int allocImage( const unsigned int &width, const unsigned int &height ); // for new image
        int freeImage();

        //
        // Functions for transfering an image between a CPU and a GPU
        // There are friend funcions of the TIFF, JPEG and PNG image class
        //
        /*=== Transfering an image from a host to a device ===*/
        int transferImage( const hsaImage<T> &h_image );

        /*=== Trasnfering an imge from a device to a host ===*/
        int backTransferImage( hsaImage<T> *h_image, const imagePointerNo &pointerNo ) const;
};

//
// A separated array image class on a host
//
template <class T>
class hsaImage {

  private:
    //
    // A constant for the number of image channels
    //
    static const unsigned int RGB = 3;

    //
    // Image sizes and pointers
    //
    unsigned int mWidth;
    unsigned int mHeight;
    T *mData[RGB];

    //
    // A color converted images
    // 
    T *mYComp;			// Y component image, i.e., BW image
    T *mConvData[RGB];		// color converted data such as RGB and opponent: default is RGB
    
    //
    // A flag for host memory type
    //
    int mHostMemoryType;	// pageable or page-locked	

    //
    // The constants for PNG images
    //
    static const int PNG_BYTES_TO_CHECK = 8;
    static const int DEFAULT_BIT_DEPTH = 8;
    static const int DEFAULT_COLOR_TYPE = PNG_COLOR_TYPE_RGB;	// PNG_COLOR_TYPE_RGB is defined in png.h as an integer

  public:
    //
    // The default Constructor and deconstructor
    //
    hsaImage();			// default constructor
    ~hsaImage();		// destructor

    //
    // Inline functions for getters
    //
    /*=== The number of channels ===*/
    unsigned int getNoChannel() { return RGB; }

    /*=== Image size ===*/
    unsigned int getImageWidth() { return mWidth; }
    unsigned int getImageHeight() { return mHeight; }
    void showImageSize() { std::cout << "Image size: " << mWidth << ", " << mHeight << std::endl; }

    /*=== Image pointers ===*/
    T *getImagePtr( const unsigned int &channel_no ) { return mData[channel_no]; }
    T *getYCompPtr() { return mYComp; }
    T *getConvImagePtr( const unsigned int &channel_no ) { return mConvData[channel_no]; }

    //
    // Member functions for memory allocation and free
    // The size of an image should be obtained by GetImageSize() of each image type or given by auguments
    //
    int allocImage( const hostMemoryType &hostMemoryType );
    int allocImage( const unsigned int &width, const unsigned int &height, const hostMemoryType &hostMemoryType ); // for new image
    int freeImage();

    //
    // The operator= for host images
    //
    hsaImage<T> &operator=( const hsaImage<T> &sourceImage );

    //
    // Overwrite the original data by the color converted data
    //
    void overwriteOriginalDataByConvertedData();

    //
    // For TIFF images
    //
    int tiffGetImageSize( const std::string &sImageFileName );
    int tiffReadImage( const std::string &sImageFileName );
    int tiffSaveImage( const std::string &sOutputFileName, const imagePointerNo &pointerNo ) const;

    //
    // For JPEG images
    //
    int jpegGetImageSize( const std::string &sImageFileName );
    int jpegReadImage( const std::string &sImageFileName );
    int jpegSaveImage( const std::string &sOutputFileName, const imagePointerNo &pointerNo ) const;

    //
    // For PNG images
    //
    int pngGetImageSize( const std::string &sImageFileName );
    int pngReadImage( const std::string &sImageFileName );
    int pngSaveImage( const std::string &sOutputFileName, const imagePointerNo &pointerNo ) const;

    //
    // friend function for GPU computing
    //
    friend int dsaImage<T>::transferImage( const hsaImage<T> &h_image );
    friend int dsaImage<T>::backTransferImage( hsaImage<T> *h_image, const imagePointerNo &pointerNo ) const;

    //
    // Saving pixel values
    //
    int outputYCompImagePixelValues( const std::string &sOutputFileName ) const;

};

#endif // IMAGE_RW_CUDA_H

