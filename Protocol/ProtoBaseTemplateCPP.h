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
                return static_cast<std::int32_t>(parse<std::int64_t>(pData, pBytesParsed));
            }

            static std::int64_t parse64 (const unsigned char * pData, int * pBytesParsed)
            {
                return parse<std::int64_t>(pData, pBytesParsed);
            }

            static std::int32_t parseSigned32 (const unsigned char * pData, int * pBytesParsed)
            {
                std::uint32_t rawValue = parse<std::uint32_t>(pData, pBytesParsed);
                return static_cast<std::int32_t>((rawValue >> 1) ^ ((rawValue << 31) >> 31));
            }

            static std::int64_t parseSigned64 (const unsigned char * pData, int * pBytesParsed)
            {
                std::uint64_t rawValue = parse<std::uint64_t>(pData, pBytesParsed);
                return static_cast<std::int64_t>((rawValue >> 1) ^ ((rawValue << 63) >> 63));
            }

            static std::uint32_t parseUnsigned32 (const unsigned char * pData, int * pBytesParsed)
            {
                return parse<std::uint32_t>(pData, pBytesParsed);
            }

            static std::uint64_t parseUnsigned64 (const unsigned char * pData, int * pBytesParsed)
            {
                return parse<std::uint64_t>(pData, pBytesParsed);
            }

            static std::string serialize32 (std::int32_t value) const
            {
                return serialize(value);
            }

            static std::string serialize64 (std::int64_t value) const
            {
                return serialize(value);
            }

            static std::string serializeSigned32 (std::int32_t value) const
            {
                std::uint32_t rawValue = (value << 1) ^ (value >> 31);
                return serialize(rawValue);
            }

            static std::string serializeSigned64 (std::int64_t value) const
            {
                std::uint64_t rawValue = (value << 1) ^ (value >> 63);
                return serialize(rawValue);
            }

            static std::string serializeUnsigned32 (std::uint32_t value) const
            {
                return serialize(value);
            }

            static std::string serializeUnsigned64 (std::uint64_t value) const
            {
                return serialize(value);
            }

        private:
            VarInt ()
            {}

            template <typename ValueType>
            static ValueType parse (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }
                ValueType value = 0;
                unsigned int byteCount = 0;
                unsigned int maxByteCount = sizeof(ValueType) + sizeof(ValueType) / 4;
                while (true)
                {
                    ValueType currentMaskedValue = *pData & 0x7f;
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
            static std::string serialize (ValueType value) const
            {
                std::uint64_t unsignedValue64 = value;
                std::string result;
                bool lastByte = false;
                while (!lastByte)
                {
                    unsigned char currentByte = unsignedValue64 & 0x7f;

                    unsignedValue64 >> 7;
                    if (unsignedValue64 == 0)
                    {
                        lastByte = true;
                    }
                    else
                    {
                        currentByte |= 0x80;
                    }

                    result += currentByte;
                }
                
                return result;
            }
        };

        class FixedSize
        {
        public:

            static std::int32_t parse32 (const unsigned char * pData)
            {
                return parse<std::int32_t>(pData);
            }

            static std::int64_t parse64 (const unsigned char * pData)
            {
                return parse<std::int64_t>(pData);
            }

            static std::int32_t parseSigned32 (const unsigned char * pData)
            {
                return parse<std::int32_t>(pData);
            }

            static std::int64_t parseSigned64 (const unsigned char * pData)
            {
                return parse<std::int64_t>(pData);
            }

            static float parseFloat (const unsigned char * pData)
            {
                return parse<float>(pData);
            }

            static double parseDouble (const unsigned char * pData)
            {
                return parse<double>(pData);
            }

            static std::string serialize32 (std::int32_t value) const
            {
                return serialize(value);
            }

            static std::string serialize64 (std::int64_t value) const
            {
                return serialize(value);
            }

            static std::string serializeSigned32 (std::int32_t value) const
            {
                return serialize(value);
            }

            static std::string serializeSigned64 (std::int64_t value) const
            {
                return serialize(value);
            }

            static std::string serializeFloat (float value) const
            {
                return serialize(value);
            }

            static std::string serializeDouble (double value) const
            {
                return serialize(value);
            }

        private:
            FixedSize ()
            {}

            template <typename ValueType>
            static ValueType parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }
                ValueType value = 0;
                unsigned char * pValueChars = reinterpret_cast<unsigned char *>(&value);
                for (int i = sizeof(ValueType) - 1; i >= 0; --i)
                {
                    pValueChars[i] = *pData;
                    ++pData;
                }

                return value;
            }

            template <typename ValueType>
            static std::string serialize (ValueType value) const
            {
                std::string result;
                unsigned char * pValueChars = reinterpret_cast<unsigned char *>(&value);
                for (int i = sizeof(ValueType) - 1; i >= 0; --i)
                {
                    result += pValueChars[i];
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

            virtual size_t parse (const unsigned char * pData)
            {
                size_t bytesParsed = 0;
                int boolValue = VarInt::parse32(pData, &bytesParsed);
                if (bytesParsed != 1)
                {
                    throw ProtocolBufferException("Boolean VarInt length exceeded one byte.");
                }

                if (boolValue == 0)
                {
                    setValue(false);
                }
                else if (boolValue == 1)
                {
                    setValue(true);
                }
                else
                {
                    throw ProtocolBufferException("Boolean VarInt contained invalid value.");
                }

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                return VarInt::serialize32(value() ? 1 : 0);
            }
        };

        class ProtoInt32 : public ProtoNumericType<std::int32_t>
        {
        public:
            explicit ProtoInt32 (std::int32_t defaultValue = 0)
            : ProtoNumericType<std::int32_t>(0, defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                size_t bytesParsed = 0;
                std::int32_t intValue = VarInt::parse32(pData, &bytesParsed);

                setValue(intValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                int32_t intValue = value();

                return VarInt::serialize32(intValue);
            }
        };

        class ProtoInt64 : public ProtoNumericType<std::int64_t>
        {
        public:
            explicit ProtoInt64 (std::int64_t defaultValue = 0)
            : ProtoNumericType<std::int64_t>(0, defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                size_t bytesParsed = 0;
                std::int64_t intValue = VarInt::parse64(pData, &bytesParsed);

                setValue(intValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                int64_t intValue = value();

                return VarInt::serialize64(intValue);
            }
        };

        class ProtoUnsignedInt32 : public ProtoNumericType<std::uint32_t>
        {
        public:
            explicit ProtoUnsignedInt32 (std::uint32_t defaultValue = 0)
            : ProtoNumericType<std::uint32_t>(0, defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                size_t bytesParsed = 0;
                std::uint32_t intValue = VarInt::parseUnsigned32(pData, &bytesParsed);

                setValue(intValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                uint32_t intValue = value();

                return VarInt::serializeUnsigned32(intValue);
            }
        };

        class ProtoUnsignedInt64 : public ProtoNumericType<std::uint64_t>
        {
        public:
            explicit ProtoUnsignedInt64 (std::uint64_t defaultValue = 0)
            : ProtoNumericType<std::uint64_t>(0, defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                size_t bytesParsed = 0;
                std::uint64_t intValue = VarInt::parseUnsigned64(pData, &bytesParsed);

                setValue(intValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                uint64_t intValue = value();

                return VarInt::serializeUnsigned64(intValue);
            }
        };

        class ProtoSignedInt32 : public ProtoNumericType<std::int32_t>
        {
        public:
            explicit ProtoSignedInt32 (std::int32_t defaultValue = 0)
            : ProtoNumericType<std::int32_t>(0, defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                size_t bytesParsed = 0;
                std::int32_t intValue = VarInt::parseSigned32(pData, &bytesParsed);

                setValue(intValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                int32_t intValue = value();

                return VarInt::serializeSigned32(intValue);
            }
        };

        class ProtoSignedInt64 : public ProtoNumericType<std::int64_t>
        {
        public:
            explicit ProtoSignedInt64 (std::int64_t defaultValue = 0)
            : ProtoNumericType<std::int64_t>(0, defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                size_t bytesParsed = 0;
                std::int64_t intValue = VarInt::parseSigned64(pData, &bytesParsed);

                setValue(intValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                int64_t intValue = value();

                return VarInt::serializeSigned64(intValue);
            }
        };

        class ProtoFixed32 : public ProtoNumericType<std::int32_t>
        {
        public:
            explicit ProtoFixed32 (std::int32_t defaultValue = 0)
            : ProtoNumericType<std::int32_t>(0, defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                std::int32_t intValue = FixedSize::parse32(pData);

                setValue(intValue);

                return 4;
            }

            virtual std::string serialize () const
            {
                int32_t intValue = value();

                return FixedSize::serialize32(intValue);
            }

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

            virtual size_t parse (const unsigned char * pData)
            {
                std::int64_t intValue = FixedSize::parse64(pData);

                setValue(intValue);

                return 8;
            }

            virtual std::string serialize () const
            {
                int64_t intValue = value();

                return FixedSize::serialize64(intValue);
            }

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

            virtual size_t parse (const unsigned char * pData)
            {
                float floatValue = FixedSize::parseFloat(pData);

                setValue(floatValue);

                return 4;
            }

            virtual std::string serialize () const
            {
                float floatValue = value();

                return FixedSize::serializeFloat(floatValue);
            }

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

            virtual size_t parse (const unsigned char * pData)
            {
                double doubleValue = FixedSize::parseDouble(pData);

                setValue(doubleValue);

                return 8;
            }

            virtual std::string serialize () const
            {
                double doubleValue = value();

                return FixedSize::parseDouble(doubleValue);
            }

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