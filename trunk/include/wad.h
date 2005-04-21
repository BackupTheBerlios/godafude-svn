#ifndef WAD_H
#define WAD_H

#include <string>
#include <vector>

#include <QDataStream>

class QIODevice;
class QFile;
class QString;

//! The namespace for everything related to .WAD files
namespace wad
{
    class Lump
    {
        public:
            Lump();            
            Lump( unsigned ofs, unsigned len, const std::string& );

            inline const std::string &name() const { return name_; }
            inline std::string name() { return name_; }
            
            inline const unsigned len() const { return len_; }
            
            friend class Wad;

        private:
            quint32 ofs_;
            quint32 len_;
            std::string name_;
    };

    //! A class that represents a single IWAD or PWAD file
    /*!
     *  Long description goes here
     */
    class Wad
    {
        public:
            class IOError {};
            class BadFormat {};
            
            typedef std::vector<Lump>::const_iterator const_iterator;
            typedef std::vector<Lump>::iterator iterator;
            
            //! Constructs a WAD object using an IO device
            /*!
             *  The WAD is opened and its directory read. The device
             *  must be non-sequential and readable.
             *
             * \param source The data source to open. It will be deleted
             *  automatically by the destructor. (It the constructor
	     *  fails, it will be deleted, too.)
	     *
             * \throw File::IOError If \a source is not valid
             * \throw File::BadFormat If \a source is not in WAD format
             */
            Wad( QIODevice *source );
            virtual ~Wad();
            
            virtual const QString &name() const = 0;
            
            //! Returns a readable stream to the data
            /*!
             * You should use Wad::seek before using the stream
             */
            inline QDataStream &stream() { return stream_; }
            
            //! True, if this is an IWAD
            inline bool isIWAD() const { return isiwad_; }
            
            //! True, if the WAD contains a lump called MAPINFO
            /*!
             *  The actual test will run only once, when you call
             *  the function for the first time
             */   
            bool isHexen() const;
            
            //! Returns the number of lumps in the WAD directory
            inline unsigned numberOfLumps() const { return numberOfLumps_; }
            
            iterator find( const std::string &lumpName );
            const_iterator find( const std::string &lumpName ) const;
            inline const_iterator begin() const { return dir_.begin(); }
            inline iterator begin() { return dir_.begin(); }
            inline const_iterator end() const { return dir_.end(); }
            inline iterator end() { return dir_.end(); }
            
            //! Sets Wad::stream to the beginning of the given lump
            /*!
             * \throws IOError if that doesn't work
             */
            void seek( const Lump &l );
            
        private:
            QIODevice *source_;
            QDataStream stream_;          
            bool isiwad_;
            mutable enum { yes, no, unknown } ishexen_;            

            unsigned numberOfLumps_;
            unsigned directoryOffset_;
            std::vector<Lump> dir_;
    };
    
    class File : public Wad
    {
        public:
            File( const QString &filename );
            
            const QString &name() const;

        private:
            const QString filename_;
    };
    
    class Collection
    {
        public:
            Collection();
            
            Collection &operator+=( File &f );

    };
}

#endif
