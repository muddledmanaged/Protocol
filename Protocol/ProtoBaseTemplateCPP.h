const string Protocol::CodeGeneratorCPP::mProtoBaseHeaderFileTemplate =

R"MuddledManaged(namespace MuddledManaged
{
    namespace Protocol
    {
        class ProtocolBufferException : public std::runtime_error
        {
        public:
            ProtocolBufferException (const std::string & message = std::string(""))
            : std::runtime_error("")
            {
                if (message.size() != 0)
                {
                    mMessage = message;
                }
                else
                {
                    mMessage = "Error in protocol buffer.";
                }
            }

            virtual ~ProtocolBufferException ()
            { }

            virtual const char * what () const noexcept
            {
                return mMessage.c_str();
            }

        protected:
            ProtocolBufferException ()
            : std::logic_error("")
            { }

            std::string mMessage;
        };
        
        class VarInt
        {
        public:
            static int size (unsigned long long value)
            {
                if (value < (1ull << 7))
                {
                    return 1;
                }
                else if (value < (1ull << 14))
                {
                    return 2;
                }
                else if (value < (1ull << 21))
                {
                    return 3;
                }
                else if (value < (1ull << 28))
                {
                    return 4;
                }
                else if (value < (1ull << 35))
                {
                    return 5;
                }
                else if (value < (1ull << 42))
                {
                    return 6;
                }
                else if (value < (1ull << 49))
                {
                    return 7;
                }
                else if (value < (1ull << 56))
                {
                    return 8;
                }
                else if (value < (1ull << 63))
                {
                    return 9;
                }
                return 10;
            }

            static int sizeIndex (unsigned long long index)
            {
                return sizeVarInt(index << 3);
            }

            static std::int32_t parse32 (const unsigned char * pData, int * pBytesParsed)
            {
                return static_cast<std::int32_t>(parseUnsigned<std::uint64_t>(pData, pBytesParsed, 10));
            }

            static std::int64_t parse64 (const unsigned char * pData, int * pBytesParsed)
            {
                return static_cast<std::int64_t>(parseUnsigned<std::uint64_t>(pData, pBytesParsed, 10));
            }

            static std::int32_t parseSigned32 (const unsigned char * pData, int * pBytesParsed)
            {
                std::uint32_t rawValue = parseUnsigned<std::uint32_t>(pData, pBytesParsed, 5);
                return static_cast<std::int32_t>(rawValue >> 1) ^ (static_cast<std::int32_t>(rawValue << 31) >> 31);
            }

            static std::int64_t parseSigned64 (const unsigned char * pData, int * pBytesParsed)
            {
                std::uint64_t rawValue = parseUnsigned<std::uint64_t>(pData, pBytesParsed, 10);
                return static_cast<std::int64_t>(rawValue >> 1) ^ (static_cast<std::int64_t>(rawValue << 63) >> 63);
            }

            static std::uint32_t parseUnsigned32 (const unsigned char * pData, int * pBytesParsed)
            {
                return parseUnsigned<std::uint32_t>(pData, pBytesParsed, 5);
            }

            static std::uint64_t parseUnsigned64 (const unsigned char * pData, int * pBytesParsed)
            {
                return parseUnsigned<std::uint64_t>(pData, pBytesParsed, 10);
            }

            static std::string serialize32 (std::int32_t value) const
            {
                return serializeUnsigned(static_cast<std::uint64_t>(static_cast<std::int64_t>(value)));
            }

            static std::string serialize64 (std::int64_t value) const
            {
                return serializeUnsigned(static_cast<std::uint64_t>(value));
            }

            static std::string serializeSigned32 (std::int32_t value) const
            {
                std::uint32_t rawValue = (value << 1) ^ (value >> 31);
                return serializeUnsigned(rawValue);
            }

            static std::string serializeSigned64 (std::int64_t value) const
            {
                std::uint64_t rawValue = (value << 1) ^ (value >> 63);
                return serializeUnsigned(rawValue);
            }

            static std::string serializeUnsigned32 (std::uint32_t value) const
            {
                return serializeUnsigned(value);
            }

            static std::string serializeUnsigned64 (std::uint64_t value) const
            {
                return serializeUnsigned(value);
            }

        private:
            VarInt ()
            {}

            template <typename ValueType>
            static ValueType parseUnsigned (const unsigned char * pData, int * pBytesParsed, unsigned int maxByteCount)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }
                ValueType value = 0;
                int byteCount = 0;
                while (true)
                {
                    ValueType currentMaskedValue = pData & 0x7f;
                    currentMaskedValue << byteCount * 7;
                    value |= currentMaskedValue;
                    ++byteCount;

                    bool lastByte = pData & 0x80;
                    if (lastByte)
                    {
                        break;
                    }

                    ++pData;

                    if (byteCount == maxByteCount)
                    {
                        throw ProtocolBufferException("VarInt length exceeded maximum bytes.");
                    }
                }

                if (pBytesParsed != nullptr)
                {
                    *pBytesParsed = byteCount;
                }

                return value;
            }

            template <typename ValueType>
            static std::string serializeUnsigned (ValueType value) const
            {
                std::string result;
                int byteCount = 0;
                while (true)
                {
                    ValueType currentMaskedValue = value & 0x7f;
                    unsigned char currentByte = static_cast<unsigned char>(currentMaskedValue);

                    bool lastByte = false;
                    value >> 7;
                    if (value == 0)
                    {
                        lastByte = true;
                    }
                    else
                    {
                        currentByte |= 0x80;
                    }

                    result += currentByte;

                    if (lastByte)
                    {
                        break;
                    }
                    ++byteCount;
                }
                
                return result;
            }
        };

        class ProtoBase
        {
        public:
            virtual ~ProtoBase ()
            {}

            virtual void clear ()
            {
                mSet = false;
            }

            virtual int key (unsigned int index, bool packed) = 0;

            virtual size_t parse (const unsigned char * pData) = 0;

            virtual std::string serialize () const = 0;

            virtual size_t size () const = 0;

            virtual bool isSet () const
            {
                return mSet;
            }

        protected:
            ProtoBase ()
            : mSet(false)
            {}

            virtual void set ()
            {
                mSet = true;
            }

        private:
            ProtoBase (const ProtoBase & src) = delete;
            ProtoBase & operator = (const ProtoBase & rhs) = delete;

            bool mSet;
        };

        class ProtoMessage : public ProtoBase
        {
        public:
            virtual int key (unsigned int index, bool packed)
            {
                return (index << 3) | 0x02;
            }

            virtual bool isSet () const
            {
                return true;
            }

            virtual bool isValid () = 0;
        };

        template <typename NumericType>
        class ProtoNumericType : public ProtoBase
        {
        public:
            NumericType value () const
            {
                return mValue;
            }

            void setValue (NumericType value)
            {
                mValue = value;
                set();
            }

            void setValueToDefault ()
            {
                mValue = mValueDefault;
                set();
            }

            virtual int key (unsigned int index, bool packed)
            {
                if (packed)
                {
                    return (index << 3) | 0x02;
                }
                return index << 3;
            }

            virtual size_t size () const
            {
                return sizeVarInt(mValue);
            }

        protected:
            ProtoNumericType (NumericType value, NumericType defaultValue)
            : mValue(value), mValueDefault(defaultValue)
            {}

        private:
            NumericType mValue;
            NumericType mValueDefault;
        };

        template <typename EnumType>
        class ProtoEnum : public ProtoNumericType<EnumType>
        {
        public:
            explicit ProtoEnum (EnumType defaultValue = 0)
            : ProtoNumericType<EnumType>(0, defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                size_t bytesParsed = 0;
                int enumValue = VarInt::parse32(pData, &bytesParsed);

                setValue(static_cast<EnumType>(enumValue));

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                int32_t enumValue = value();

                return serialize32(enumValue);
            }
        };

        class ProtoBool : public ProtoNumericType<bool>
        {
        public:
            explicit ProtoBool (bool defaultValue = false)
            : ProtoNumericType<bool>(false, defaultValue)
            {}
        };

        class ProtoInt32 : public ProtoNumericType<std::int32_t>
        {
        public:
            explicit ProtoInt32 (std::int32_t defaultValue = 0)
            : ProtoNumericType<std::int32_t>(0, defaultValue)
            {}
        };

        class ProtoInt64 : public ProtoNumericType<std::int64_t>
        {
        public:
            explicit ProtoInt64 (std::int64_t defaultValue = 0)
            : ProtoNumericType<std::int64_t>(0, defaultValue)
            {}
        };

        class ProtoUnsignedInt32 : public ProtoNumericType<std::uint32_t>
        {
        public:
            explicit ProtoUnsignedInt32 (std::uint32_t defaultValue = 0)
            : ProtoNumericType<std::uint32_t>(0, defaultValue)
            {}
        };

        class ProtoUnsignedInt64 : public ProtoNumericType<std::uint64_t>
        {
        public:
            explicit ProtoUnsignedInt64 (std::uint64_t defaultValue = 0)
            : ProtoNumericType<std::uint64_t>(0, defaultValue)
            {}
        };

        class ProtoSignedInt32 : public ProtoNumericType<std::int32_t>
        {
        public:
            explicit ProtoSignedInt32 (std::int32_t defaultValue = 0)
            : ProtoNumericType<std::int32_t>(0, defaultValue)
            {}

            virtual void parse (const std::string & data);

            virtual std::string serialize () const;
        };

        class ProtoSignedInt64 : public ProtoNumericType<std::int64_t>
        {
        public:
            explicit ProtoSignedInt64 (std::int64_t defaultValue = 0)
            : ProtoNumericType<std::int64_t>(0, defaultValue)
            {}

            virtual void parse (const std::string & data);

            virtual std::string serialize () const;
        };

        class ProtoFixed32 : public ProtoNumericType<std::int32_t>
        {
        public:
            explicit ProtoFixed32 (std::int32_t defaultValue = 0)
            : ProtoNumericType<std::int32_t>(0, defaultValue)
            {}

            virtual void parse (const std::string & data);

            virtual std::string serialize () const;

            virtual size_t size () const
            {
                return 4;
            }
        };

        class ProtoFixed64 : public ProtoNumericType<std::int64_t>
        {
        public:
            explicit ProtoFixed64 (std::int64_t defaultValue = 0)
            : ProtoNumericType<std::int64_t>(0, defaultValue)
            {}

            virtual void parse (const std::string & data);

            virtual std::string serialize () const;

            virtual size_t size () const
            {
                return 8;
            }
        };

        class ProtoSignedFixed32 : public ProtoFixed32
        {
        public:
            explicit ProtoSignedFixed32 (std::int32_t defaultValue = 0)
            : ProtoFixed32(defaultValue)
            {}
        };

        class ProtoSignedFixed64 : public ProtoFixed64
        {
        public:
            explicit ProtoSignedFixed64 (std::int64_t defaultValue = 0)
            : ProtoFixed64(defaultValue)
            {}
        };

        class ProtoFloat : public ProtoNumericType<float>
        {
        public:
            explicit ProtoFloat (float defaultValue = 0)
            : ProtoNumericType<float>(0, defaultValue)
            {}

            virtual void parse (const std::string & data);

            virtual std::string serialize () const;

            virtual size_t size () const
            {
                return 4;
            }
        };

        class ProtoDouble : public ProtoNumericType<double>
        {
        public:
            explicit ProtoDouble (double defaultValue = 0)
            : ProtoNumericType<double>(0, defaultValue)
            {}

            virtual void parse (const std::string & data);

            virtual std::string serialize () const;

            virtual size_t size () const
            {
                return 8;
            }
        };

        class ProtoStringType : public ProtoBase
        {
        public:
            std::string value () const
            {
                return mValue;
            }

            void setValue (const std::string & value)
            {
                mValue = value;
                set();
            }

            void setValueToDefault ()
            {
                mValue = mValueDefault;
                set();
            }

            virtual int key (unsigned int index, bool packed)
            {
                return (index << 3) | 0x02;
            }

            virtual void parse (const std::string & data);

            virtual std::string serialize () const;

            virtual size_t size () const
            {
                return mValue.size();
            }

        protected:
            ProtoStringType (const std::string & value, const std::string & defaultValue)
            : mValue(value), mValueDefault(defaultValue)
            {}
            
        private:
            std::string mValue;
            std::string mValueDefault;
        };
        
        class ProtoString : public ProtoStringType
        {
        public:
            explicit ProtoString (const std::string & defaultValue = "")
            : ProtoStringType("", defaultValue)
            {}
        };
        
        class ProtoBytes : public ProtoStringType
        {
        public:
            explicit ProtoBytes ()
            : ProtoStringType("", "")
            {}
        };
    }
}
)MuddledManaged";