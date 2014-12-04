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
        
        class PrimitiveEncoding
        {
        public:
            static unsigned int sizeVariableInt (unsigned long long value)
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

            static unsigned int sizeIndex (unsigned long long index)
            {
                return sizeInt(index << 3);
            }

            static std::int32_t parseVariableInt32 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return static_cast<std::int32_t>(parseVariable<std::int64_t>(pData, pBytesParsed));
            }

            static std::vector<std::int32_t> parsePackedVariableInt32 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedVariable<std::int32_t, std::int64_t>(pData, pBytesParsed);
            }

            static std::int32_t parseFixedInt32 (const unsigned char * pData)
            {
                return parseFixed<std::int32_t>(pData);
            }

            static std::vector<std::int32_t> parsePackedFixedInt32 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedFixed<std::int32_t>(pData, pBytesParsed);
            }

            static std::int64_t parseVariableInt64 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parseVariable<std::int64_t>(pData, pBytesParsed);
            }

            static std::vector<std::int64_t> parsePackedVariableInt64 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedVariable<std::int64_t, std::int64_t>(pData, pBytesParsed);
            }

            static std::int64_t parseFixedInt64 (const unsigned char * pData)
            {
                return parseFixed<std::int64_t>(pData);
            }

            static std::vector<std::int64_t> parsePackedFixedInt64 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedFixed<std::int64_t>(pData, pBytesParsed);
            }

            static std::int32_t parseVariableSignedInt32 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parseVariable<std::int32_t>(pData, pBytesParsed, true);
            }

            static std::vector<std::int32_t> parsePackedVariableSignedInt32 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedVariable<std::int32_t, std::int32_t>(pData, pBytesParsed, true);
            }

            static std::int32_t parseFixedSignedInt32 (const unsigned char * pData)
            {
                return parseFixed<std::int32_t>(pData);
            }

            static std::vector<std::int32_t> parsePackedFixedSignedInt32 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedFixed<std::int32_t>(pData, pBytesParsed);
            }

            static std::int64_t parseVariableSignedInt64 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parseVariable<std::int64_t>(pData, pBytesParsed, true);
            }

            static std::vector<std::int64_t> parsePackedVariableSignedInt64 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedVariable<std::int64_t, std::int64_t>(pData, pBytesParsed, true);
            }

            static std::int64_t parseFixedSignedInt64 (const unsigned char * pData)
            {
                return parseFixed<std::int64_t>(pData);
            }

            static std::vector<std::int64_t> parsePackedFixedSignedInt64 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedFixed<std::int64_t>(pData, pBytesParsed);
            }

            static std::uint32_t parseVariableUnsignedInt32 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parseVariable<std::uint32_t>(pData, pBytesParsed);
            }

            static std::vector<std::uint32_t> parsePackedVariableUnsignedInt32 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedVariable<std::uint32_t, std::uint32_t>(pData, pBytesParsed);
            }

            static std::uint64_t parseVariableUnsignedInt64 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parseVariable<std::uint64_t>(pData, pBytesParsed);
            }

            static std::vector<std::uint64_t> parsePackedVariableUnsignedInt64 (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedVariable<std::uint64_t, std::uint64_t>(pData, pBytesParsed);
            }

            static float parseFloat (const unsigned char * pData)
            {
                return parseFixed<float>(pData);
            }

            static std::vector<sfloat> parsePackedFloat (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedFixed<float>(pData, pBytesParsed);
            }

            static double parseDouble (const unsigned char * pData)
            {
                return parseFixed<double>(pData);
            }

            static std::vector<double> parsePackedDouble (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parsePackedFixed<double>(pData, pBytesParsed);
            }

            static std::string parseString (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                return parseBytes(pData, pBytesParsed);
            }

            static std::string parseBytes (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }
                unsigned int bytesParsed = 0;
                std::uint32_t length = parseUnsigned32(pData, &bytesParsed);
                pData += bytesParsed;

                std::string result;
                for (unsigned int i = 0; i < length; ++i)
                {
                    result += *pData;
                    ++pData;
                }

                if (pBytesParsed != nullptr)
                {
                    *pBytesParsed = bytesParsed + length;
                }

                return result;
            }

            static std::string serializeVariableInt32 (std::int32_t value) const
            {
                return serializeVariable<std::int64_t>(value);
            }

            static std::string serializePackedVariableInt32 (const std::vector<std::int32_t> & values) const
            {
                return serializePackedVariable<std::int32_t, std::int64_t>(values);
            }

            static std::string serializeFixedInt32 (std::int32_t value) const
            {
                return serializeFixed<std::int32_t>(value);
            }

            static std::string serializePackedFixedInt32 (const std::vector<std::int32_t> & values) const
            {
                return serializePackedFixed<std::int32_t>(values);
            }

            static std::string serializeVariableInt64 (std::int64_t value) const
            {
                return serializeVariable<std::int64_t>(value);
            }

            static std::string serializePackedVariableInt64 (const std::vector<std::int64_t> & values) const
            {
                return serializePackedVariable<std::int64_t, std::int64_t>(values);
            }

            static std::string serializeFixedInt64 (std::int64_t value) const
            {
                return serializeFixed<std::int64_t>(value);
            }

            static std::string serializePackedFixedInt64 (const std::vector<std::int64_t> & values) const
            {
                return serializePackedFixed<std::int64_t>(values);
            }

            static std::string serializeVariableSignedInt32 (std::int32_t value) const
            {
                return serializeVariable<std::int32_t>(value, true);
            }

            static std::string serializePackedVariableSignedInt32 (const std::vector<std::int32_t> & values) const
            {
                return serializePackedVariable<std::int32_t, std::int32_t>(values, true);
            }

            static std::string serializeFixedSignedInt32 (std::int32_t value) const
            {
                return serializeFixed<std::int32_t>(value);
            }

            static std::string serializePackedFixedSignedInt32 (const std::vector<std::int32_t> & values) const
            {
                return serializePackedFixed<std::int32_t>(values);
            }

            static std::string serializeVariableSignedInt64 (std::int64_t value) const
            {
                return serializeVariable<std::int64_t>(value, true);
            }

            static std::string serializePackedVariableSignedInt64 (const std::vector<std::int64_t> & values) const
            {
                return serializePackedVariable<std::int64_t, std::int64_t>(values, true);
            }

            static std::string serializeFixedSignedInt64 (std::int64_t value) const
            {
                return serializeFixed<std::int64_t>(value);
            }

            static std::string serializePackedFixedSignedInt64 (const std::vector<std::int64_t> & values) const
            {
                return serializePackedFixed<std::int64_t>(values);
            }

            static std::string serializeVariableUnsignedInt32 (std::uint32_t value) const
            {
                return serializeVariable<std::uint32_t>(value);
            }

            static std::string serializePackedVariableUnsignedInt32 (const std::vector<std::uint32_t> values) const
            {
                return serializePackedVariable<std::uint32_t, std::uint32_t>(values);
            }

            static std::string serializeVariableUnsignedInt64 (std::uint64_t value) const
            {
                return serializeVariable<std::uint64_t>(value);
            }

            static std::string serializePackedVariableUnsignedInt64 (const std::vector<std::uint64_t> values) const
            {
                return serializePackedVariable<std::uint64_t, std::uint64_t>(values);
            }

            static std::string serializeFloat (float value) const
            {
                return serializeFixed<float>(value);
            }

            static std::string serializePackedFloat (const std::vector<float> & values) const
            {
                return serializePackedFixed<float>(values);
            }

            static std::string serializeDouble (double value) const
            {
                return serializeFixed<double>(value);
            }

            static std::string serializePackedDouble (const std::vector<double> & values) const
            {
                return serializePackedFixed<double>(values);
            }

            static std::string serializeString (const std::string & value) const
            {
                return serializeBytes(value);
            }

            static std::string serializeBytes (const std::string & value) const
            {
                std::string result;

                result = serializeVariableUnsignedInt32(value.length());
                result += value;

                return result;
            }

        private:
            PrimitiveEncoding ()
            {}

            template <typename ValueType>
            static ValueType parseVariable (const unsigned char * pData, unsigned int * pBytesParsed, bool useZigZag = false)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }
                ValueType rawValue = 0;
                unsigned int byteCount = 0;
                unsigned int maxByteCount = sizeof(ValueType) + sizeof(ValueType) / 4;
                while (true)
                {
                    ValueType currentMaskedValue = *pData & 0x7f;
                    currentMaskedValue << byteCount * 7;
                    rawValue |= currentMaskedValue;
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

                if (useZigZag)
                {
                    typename std::make_unsigned<ValueType>::type unsignedValue = rawValue;
                    typename std::make_signed<ValueType>::type signedValue = rawValue;

                    int shiftAmount = sizeof(ValueType) * 8 - 1;
                    return (unsignedValue >> 1) ^ ((signedValue << shiftAmount) >> shiftAmount);
                }
                else
                {
                    return rawValue;
                }
            }

            template <typename ValueType>
            static ValueType parseFixed (const unsigned char * pData)
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

            template <typename ValueType, typename PackedType>
            static std::vector<ValueType> parsePackedVariable (const unsigned char * pData, unsigned int * pBytesParsed, bool useZigZag = false)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }
                unsigned int bytesParsed = 0;
                std::uint32_t length = parseUnsigned32(pData, &bytesParsed);
                pData += bytesParsed;

                std::vector<ValueType> result;
                std::uint32_t remainingBytes = length;
                while (remainingBytes)
                {
                    unsigned int packedBytesParsed = 0;
                    PackedType packedValue = parseVariable<PackedType>(pData, &packedBytesParsed, useZigZag);
                    result.push_back(static_cast<ValueType>(packedValue));
                    pData += packedBytesParsed;
                    remainingBytes -= packedBytesParsed;
                }

                if (pBytesParsed != nullptr)
                {
                    *pBytesParsed = bytesParsed + length;
                }

                return result;
            }

            template <typename ValueType>
            static std::vector<ValueType> parsePackedFixed (const unsigned char * pData, unsigned int * pBytesParsed)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }
                unsigned int bytesParsed = 0;
                std::uint32_t length = parseUnsigned32(pData, &bytesParsed);
                pData += bytesParsed;

                std::vector<ValueType> result;
                std::uint32_t itemCount = length / sizeof(ValueType);
                for (int i = 0; i < itemCount, ++i)
                {
                    ValueType packedValue = parseFixed<ValueType>(pData);
                    result.push_back(packedValue);
                    pData += sizeof(ValueType);
                }

                if (pBytesParsed != nullptr)
                {
                    *pBytesParsed = bytesParsed + length;
                }

                return result;
            }

            template <typename ValueType>
            static std::string serializeVariable (ValueType value, bool useZigZag = false) const
            {
                typename std::make_unsigned<ValueType>::type unsignedValue = value;

                if (useZigZag)
                {
                    typename std::make_signed<ValueType>::type signedValue = value;

                    int shiftAmount = sizeof(ValueType) * 8 - 1;
                    unsignedValue = (unsignedValue << 1) ^ (signedValue >> shiftAmount);
                }
                std::string result;
                bool lastByte = false;
                while (!lastByte)
                {
                    unsigned char currentByte = unsignedValue & 0x7f;

                    unsignedValue >> 7;
                    if (unsignedValue == 0)
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

            template <typename ValueType>
            static std::string serializeFixed (ValueType value) const
            {
                std::string result;
                unsigned char * pValueChars = reinterpret_cast<unsigned char *>(&value);
                for (int i = sizeof(ValueType) - 1; i >= 0; --i)
                {
                    result += pValueChars[i];
                }

                return result;
            }

            template <typename ValueType, typename PackedType>
            static std::string serializePackedVariable (const std::vector<ValueType> & values, bool useZigZag = false) const
            {
                std::string result;

                for (auto packedValue: values)
                {
                    result += serializeVariable<PackedType>(packedValue, useZigZag);
                }
                result = serializeVariableUnsignedInt32(result.length()) + result;

                return result;
            }

            template <typename ValueType>
            static std::string serializePackedFixed (const std::vector<ValueType> & values) const
            {
                std::string result;

                for (auto packedValue: values)
                {
                    result += serializeFixed<ValueType>(packedValue);
                }
                result = serializeVariableUnsignedInt32(result.length()) + result;

                return result;
            }
        };

        class ProtoBase
        {
        public:
            virtual ~ProtoBase ()
            {}

            virtual unsigned int index ()
            {
                return mIndex;
            }

            virtual void setIndex (unsigned int index)
            {
                mIndex = index;
            }

            virtual bool required ()
            {
                return mRequired;
            }

            virtual void setRequired (bool required)
            {
                mRequired = required;
            }

            virtual unsigned int key () = 0;

            virtual size_t parse (const unsigned char * pData) = 0;

            virtual std::string serialize () const = 0;

            virtual size_t size () const = 0;

            virtual bool valid ()
            {
                if (required() && !hasValue())
                {
                    return false;
                }
                return true;
            }

        protected:
            ProtoBase ()
            : mIndex(0), mHasValue(false), mRequired(false)
            {}

            virtual bool hasValue () const
            {
                return mHasValue;
            }

            virtual void setValue ()
            {
                mHasValue = true;
            }

            virtual void clearValue ()
            {
                mHasValue = false;
            }

        private:
            ProtoBase (const ProtoBase & src) = delete;
            ProtoBase & operator = (const ProtoBase & rhs) = delete;

            unsigned int mIndex;
            bool mHasValue;
            bool mRequired;
        };

        class ProtoMessage : public ProtoBase
        {
        public:
            virtual unsigned int key ()
            {
                return (index() << 3) | 0x02;
            }

        protected:
            ProtoMessage ()
            {
                setValueSet();
            }
        };

        template <typename MessageType>
        class ProtoMessageCollection : public ProtoBase
        {
        public:
            typedef std::vector<std::shared_ptr<MessageType>> CollectionType;

            virtual CollectionType * collection ()
            {
                return &mCollection;
            }

            virtual unsigned int key ()
            {
                return (index() << 3) | 0x02;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                std::shared_ptr<MessageType> message(new MessageType());
                size_t bytesParsed = message->parse(pData);

                mCollection.push_back(message);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & message : mCollection)
                {
                    result += message->serialize();
                }

                return result;
            }

            virtual bool hasValue () const
            {
                return !mCollection.empty();
            }

            virtual bool valid ()
            {
                if (mCollection.empty())
                {
                    if (required())
                    {
                        return false;
                    }
                }
                else
                {
                    for (auto & message: mCollection)
                    {
                        if (!message->valid())
                        {
                            return false;
                        }
                    }
                }
                return true;
            }

        private:
            CollectionType mCollection;
        };

        template <typename NumericType>
        class ProtoNumericType : public ProtoBase
        {
        public:
            virtual NumericType value () const
            {
                return mValue;
            }

            virtual void setValue (NumericType value)
            {
                mValue = value;
                ProtoBase::setValue();
            }

            virtual void setValueToDefault ()
            {
                mValue = mValueDefault;
                ProtoBase::setValue();
            }

            virtual bool hasValue () const
            {
                return ProtoBase::hasValue();
            }

            virtual void clearValue ()
            {
                mValue = mValueInitial;
                ProtoBase::clearValue();
            }

            virtual unsigned int key ()
            {
                return (index() << 3);
            }

            virtual size_t size () const
            {
                return sizeVarInt(mValue);
            }

        protected:
            ProtoNumericType (NumericType value, NumericType defaultValue)
            : mValue(value), mValueInitial(value), mValueDefault(defaultValue)
            {}

        private:
            NumericType mValue;
            NumericType mValueInitial;
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

        template <typename EnumType>
        class ProtoEnumCollection : public ProtoBase
        {
        public:
            typedef std::vector<ProtoEnum<EnumType>> CollectionType;

            virtual CollectionType * collection ()
            {
                return &mCollection;
            }

            virtual unsigned int key ()
            {
                if (packed())
                {
                    return (index() << 3) | 0x02;
                }
                return (index() << 3);
            }

            virtual size_t parse (const unsigned char * pData)
            {
                ProtoEnum<EnumType> value;
                size_t bytesParsed = value->parse(pData);

                mCollection.push_back(value);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & value : mCollection)
                {
                    result += value->serialize();
                }

                return result;
            }

            virtual bool hasValue () const
            {
                return !mCollection.empty();
            }

            virtual bool valid ()
            {
                if (mCollection.empty())
                {
                    if (isRequired())
                    {
                        return false;
                    }
                }
                return true;
            }

            virtual bool packed ()
            {
                return mPacked;
            }
            
        private:
            CollectionType mCollection;
            bool mPacked;
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

            virtual unsigned int key ()
            {
                return (index() << 3) | 0x05;
            }

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

            virtual unsigned int key ()
            {
                return (index() << 3) | 0x01;
            }

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

            virtual unsigned int key ()
            {
                return (index() << 3) | 0x05;
            }

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

            virtual unsigned int key ()
            {
                return (index() << 3) | 0x01;
            }

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
            virtual std::string value () const
            {
                return mValue;
            }

            virtual void setValue (const std::string & value)
            {
                mValue = value;
                ProtoBase::setValue();
            }

            virtual void setValueToDefault ()
            {
                mValue = mValueDefault;
                ProtoBase::setValue();
            }

            virtual bool hasValue () const
            {
                return ProtoBase::hasValue();
            }

            virtual void clearValue ()
            {
                mValue = mValueInitial;
                ProtoBase::clearValue();
            }

            virtual unsigned int key ()
            {
                return (index() << 3) | 0x02;
            }

            virtual void parse (const std::string & data);

            virtual std::string serialize () const;

            virtual size_t size () const
            {
                return mValue.size();
            }

        protected:
            ProtoStringType (const std::string & value, const std::string & defaultValue)
            : mValue(value), mValueInitial(value), mValueDefault(defaultValue)
            {}
            
        private:
            std::string mValue;
            std::string mValueInitial;
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