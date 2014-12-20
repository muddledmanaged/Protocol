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
            : std::runtime_error("")
            { }

            std::string mMessage;
        };
        
        class PrimitiveEncoding
        {
        public:
            static size_t sizeVariableInt32 (std::int32_t value)
            {
                return sizeVariableUnsignedInt32(static_cast<std::uint32_t>(value));
            }
            
            static size_t sizeVariableUnsignedInt32 (std::uint32_t value)
            {
                std::uint32_t shiftBit = 1;

                if (value < (shiftBit << 7))
                {
                    return 1;
                }
                else if (value < (shiftBit << 14))
                {
                    return 2;
                }
                else if (value < (shiftBit << 21))
                {
                    return 3;
                }
                else if (value < (shiftBit << 28))
                {
                    return 4;
                }
                return 5;
            }

            static size_t sizeVariableSignedInt32 (std::int32_t value)
            {
                std::uint32_t unsignedValue = static_cast<std::uint32_t>(value);

                unsignedValue = (unsignedValue << 1) ^ (value >> 31);

                return sizeVariableUnsignedInt32(unsignedValue);
            }

            static size_t sizeVariableInt64 (std::int64_t value)
            {
                return sizeVariableUnsignedInt64(static_cast<std::uint64_t>(value));
            }

            static size_t sizeVariableUnsignedInt64 (std::uint64_t value)
            {
                std::uint64_t shiftBit = 1;

                if (value < (shiftBit << 7))
                {
                    return 1;
                }
                else if (value < (shiftBit << 14))
                {
                    return 2;
                }
                else if (value < (shiftBit << 21))
                {
                    return 3;
                }
                else if (value < (shiftBit << 28))
                {
                    return 4;
                }
                else if (value < (shiftBit << 35))
                {
                    return 5;
                }
                else if (value < (shiftBit << 42))
                {
                    return 6;
                }
                else if (value < (shiftBit << 49))
                {
                    return 7;
                }
                else if (value < (shiftBit << 56))
                {
                    return 8;
                }
                else if (value < (shiftBit << 63))
                {
                    return 9;
                }
                return 10;
            }

            static size_t sizeVariableSignedInt64 (std::int64_t value)
            {
                std::uint64_t unsignedValue = static_cast<std::uint64_t>(value);

                unsignedValue = (unsignedValue << 1) ^ (value >> 63);

                return sizeVariableUnsignedInt64(unsignedValue);
            }

            static std::int32_t parseVariableInt32 (const unsigned char * pData, size_t * pBytesParsed)
            {
                return parseVariable<std::int32_t>(pData, pBytesParsed);
            }

            static std::int32_t parseFixedInt32 (const unsigned char * pData)
            {
                return parseFixed<std::int32_t>(pData);
            }

            static std::int64_t parseVariableInt64 (const unsigned char * pData, size_t * pBytesParsed)
            {
                return parseVariable<std::int64_t>(pData, pBytesParsed);
            }

            static std::int64_t parseFixedInt64 (const unsigned char * pData)
            {
                return parseFixed<std::int64_t>(pData);
            }

            static std::int32_t parseVariableSignedInt32 (const unsigned char * pData, size_t * pBytesParsed)
            {
                return parseVariable<std::int32_t>(pData, pBytesParsed, true);
            }

            static std::int32_t parseFixedSignedInt32 (const unsigned char * pData)
            {
                return parseFixed<std::int32_t>(pData);
            }

            static std::int64_t parseVariableSignedInt64 (const unsigned char * pData, size_t * pBytesParsed)
            {
                return parseVariable<std::int64_t>(pData, pBytesParsed, true);
            }

            static std::int64_t parseFixedSignedInt64 (const unsigned char * pData)
            {
                return parseFixed<std::int64_t>(pData);
            }

            static std::uint32_t parseVariableUnsignedInt32 (const unsigned char * pData, size_t * pBytesParsed)
            {
                return parseVariable<std::uint32_t>(pData, pBytesParsed);
            }

            static std::uint64_t parseVariableUnsignedInt64 (const unsigned char * pData, size_t * pBytesParsed)
            {
                return parseVariable<std::uint64_t>(pData, pBytesParsed);
            }

            static float parseFloat (const unsigned char * pData)
            {
                return parseFixed<float>(pData);
            }

            static double parseDouble (const unsigned char * pData)
            {
                return parseFixed<double>(pData);
            }

            static std::string parseString (const unsigned char * pData, size_t * pBytesParsed)
            {
                return parseBytes(pData, pBytesParsed);
            }

            static std::string parseBytes (const unsigned char * pData, size_t * pBytesParsed)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t bytesParsed = 0;
                std::uint32_t length = parseVariableUnsignedInt32(pData, &bytesParsed);
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

            static std::string serializeVariableInt32 (std::int32_t value)
            {
                return serializeVariable<std::int64_t>(value);
            }

            static std::string serializeFixedInt32 (std::int32_t value)
            {
                return serializeFixed<std::int32_t>(value);
            }

            static std::string serializeVariableInt64 (std::int64_t value)
            {
                return serializeVariable<std::int64_t>(value);
            }

            static std::string serializeFixedInt64 (std::int64_t value)
            {
                return serializeFixed<std::int64_t>(value);
            }

            static std::string serializeVariableSignedInt32 (std::int32_t value)
            {
                return serializeVariable<std::int32_t>(value, true);
            }

            static std::string serializeFixedSignedInt32 (std::int32_t value)
            {
                return serializeFixed<std::int32_t>(value);
            }

            static std::string serializeVariableSignedInt64 (std::int64_t value)
            {
                return serializeVariable<std::int64_t>(value, true);
            }

            static std::string serializeFixedSignedInt64 (std::int64_t value)
            {
                return serializeFixed<std::int64_t>(value);
            }

            static std::string serializeVariableUnsignedInt32 (std::uint32_t value)
            {
                return serializeVariable<std::uint32_t>(value);
            }

            static std::string serializeVariableUnsignedInt64 (std::uint64_t value)
            {
                return serializeVariable<std::uint64_t>(value);
            }

            static std::string serializeFloat (float value)
            {
                return serializeFixed<float>(value);
            }

            static std::string serializeDouble (double value)
            {
                return serializeFixed<double>(value);
            }

            static std::string serializeString (const std::string & value)
            {
                return serializeBytes(value);
            }

            static std::string serializeBytes (const std::string & value)
            {
                std::string result;

                result = serializeVariableUnsignedInt32(static_cast<std::uint32_t>(value.length()));
                result += value;

                return result;
            }

        private:
            PrimitiveEncoding ()
            {}

            template <typename ValueType>
            static ValueType parseVariable (const unsigned char * pData, size_t * pBytesParsed, bool useZigZag = false)
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
                    currentMaskedValue = currentMaskedValue << byteCount * 7;
                    rawValue |= currentMaskedValue;
                    ++byteCount;

                    bool lastByte = *pData & 0x80;
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
                    typename std::make_unsigned<ValueType>::type unsignedValue =
                        static_cast<typename std::make_unsigned<ValueType>::type>(rawValue);
                    typename std::make_signed<ValueType>::type signedValue =
                        static_cast<typename std::make_signed<ValueType>::type>(rawValue);

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

            template <typename ValueType>
            static std::string serializeVariable (ValueType value, bool useZigZag = false)
            {
                typename std::make_unsigned<ValueType>::type unsignedValue =
                    static_cast<typename std::make_unsigned<ValueType>::type>(value);

                if (useZigZag)
                {
                    typename std::make_signed<ValueType>::type signedValue =
                        static_cast<typename std::make_signed<ValueType>::type>(value);

                    int shiftAmount = sizeof(ValueType) * 8 - 1;
                    unsignedValue = (unsignedValue << 1) ^ (signedValue >> shiftAmount);
                }
                std::string result;
                bool lastByte = false;
                while (!lastByte)
                {
                    unsigned char currentByte = unsignedValue & 0x7f;

                    unsignedValue = unsignedValue >> 7;
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
            static std::string serializeFixed (ValueType value)
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

            virtual unsigned int index () const
            {
                return mIndex;
            }

            virtual void setIndex (unsigned int index)
            {
                mIndex = index;
            }

            virtual bool required () const
            {
                return mRequired;
            }

            virtual void setRequired (bool required)
            {
                mRequired = required;
            }

            virtual unsigned int key () const = 0;

            virtual size_t parse (const unsigned char * pData) = 0;

            virtual std::string serialize () const = 0;

            virtual size_t size () const = 0;

            virtual bool valid () const
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
            virtual unsigned int key () const
            {
                return (index() << 3) | 0x02;
            }

        protected:
            ProtoMessage ()
            {
                setValue();
            }
        };

        template <typename MessageType>
        class ProtoMessageCollection : public ProtoBase
        {
        public:
            virtual const std::vector<std::shared_ptr<MessageType>> * collection () const
            {
                return &mCollection;
            }

            virtual std::vector<std::shared_ptr<MessageType>> * mutableCollection ()
            {
                return &mCollection;
            }

            virtual void addValue (std::shared_ptr<MessageType> & message)
            {
                message->setIndex(index());

                mCollection.push_back(message);
            }

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x02;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                std::shared_ptr<MessageType> message(new MessageType());
                size_t bytesParsed = message->parse(pData);

                addValue(message);

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

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & message : mCollection)
                {
                    result += message->size();
                }

                return result;
            }

            virtual bool hasValue () const
            {
                return !mCollection.empty();
            }

            virtual void clearValue ()
            {
                mCollection.clear();
            }

            virtual bool valid () const
            {
                if (!mCollection.empty())
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
            std::vector<std::shared_ptr<MessageType>> mCollection;
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

            virtual unsigned int key () const
            {
                return (index() << 3);
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

        template <typename NumericType, typename ProtoType>
        class ProtoNumericTypeCollection : public ProtoBase
        {
        public:
            virtual const std::vector<ProtoType> * collection () const
            {
                return &mCollection;
            }

            virtual std::vector<ProtoType> * mutableCollection ()
            {
                return &mCollection;
            }

            virtual void addValue (NumericType value)
            {
                ProtoType valueType(mValueDefault);

                valueType.setIndex(index());
                valueType.setValue(value);

                mCollection.push_back(valueType);
            }

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x02;
            }

            virtual bool hasValue () const
            {
                return !mCollection.empty();
            }

            virtual void clearValue ()
            {
                mCollection.clear();
            }

            virtual bool valid () const
            {
                return true;
            }

        protected:
            ProtoNumericTypeCollection (NumericType defaultValue)
            : mValueDefault(defaultValue)
            {}

        private:
            std::vector<ProtoType> mCollection;
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
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t bytesParsed = 0;
                std::int64_t enumValue = PrimitiveEncoding::parseVariableInt64(pData, &bytesParsed);

                setValue(static_cast<EnumType>(enumValue));

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                std::int64_t enumValue = static_cast<std::int64_t>(this->value());
                result += PrimitiveEncoding::serializeVariableInt64(enumValue);

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());

                std::int64_t enumValue = static_cast<std::int64_t>(this->value());
                result += PrimitiveEncoding::sizeVariableInt64(enumValue);

                return result;
            }
        };

        template <typename EnumType>
        class ProtoEnumCollection : public ProtoNumericTypeCollection<EnumType, ProtoEnum<EnumType>>
        {
        public:
            explicit ProtoEnumCollection (EnumType defaultValue = 0)
            : ProtoNumericTypeCollection<EnumType, ProtoEnum<EnumType>>(defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::uint32_t remainingBytes = length;
                while (remainingBytes)
                {
                    size_t bytesParsed = 0;
                    std::int64_t enumValue = PrimitiveEncoding::parseVariableInt64(pData, &bytesParsed);

                    addValue(static_cast<EnumType>(enumValue));
                    
                    pData += bytesParsed;
                    remainingBytes -= bytesParsed;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeVariableInt64(static_cast<std::int64_t>(protoValue.value()));
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::sizeVariableInt64(static_cast<std::int64_t>(protoValue.value()));
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }

                return result;
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
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t bytesParsed = 0;
                std::int32_t boolValue = PrimitiveEncoding::parseVariableInt32(pData, &bytesParsed);
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
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeVariableInt32(this->value() ? 1 : 0);
                
                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());

                result += 1;
                
                return result;
            }
        };

        class ProtoBoolCollection : public ProtoNumericTypeCollection<bool, ProtoBool>
        {
        public:
            explicit ProtoBoolCollection (bool defaultValue = false)
            : ProtoNumericTypeCollection<bool, ProtoBool>(defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                for (unsigned int i = 0; i < length; ++i)
                {
                    size_t bytesParsed = 0;
                    std::int64_t boolValue = PrimitiveEncoding::parseVariableInt32(pData, &bytesParsed);
                    if (bytesParsed != 1)
                    {
                        throw ProtocolBufferException("Boolean VarInt length exceeded one byte.");
                    }

                    if (boolValue == 0)
                    {
                        addValue(false);
                    }
                    else if (boolValue == 1)
                    {
                        addValue(true);
                    }
                    else
                    {
                        throw ProtocolBufferException("Boolean VarInt contained invalid value.");
                    }

                    pData += bytesParsed;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeVariableInt32(protoValue.value() ? 1 : 0);
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += 1;
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }

                return result;
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
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t bytesParsed = 0;
                std::int32_t numericValue = PrimitiveEncoding::parseVariableInt32(pData, &bytesParsed);

                setValue(numericValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeVariableInt32(this->value());

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::sizeVariableInt32(this->value());

                return result;
            }
        };

        class ProtoInt32Collection : public ProtoNumericTypeCollection<std::int32_t, ProtoInt32>
        {
        public:
            explicit ProtoInt32Collection (std::int32_t defaultValue = 0)
            : ProtoNumericTypeCollection<std::int32_t, ProtoInt32>(defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::uint32_t remainingBytes = length;
                while (remainingBytes)
                {
                    size_t bytesParsed = 0;
                    std::int32_t numericValue = PrimitiveEncoding::parseVariableInt32(pData, &bytesParsed);

                    addValue(numericValue);

                    pData += bytesParsed;
                    remainingBytes -= bytesParsed;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeVariableInt32(protoValue.value());
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::sizeVariableInt32(protoValue.value());
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }
                
                return result;
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
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t bytesParsed = 0;
                std::int64_t numericValue = PrimitiveEncoding::parseVariableInt64(pData, &bytesParsed);

                setValue(numericValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeVariableInt64(this->value());

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                
                result += PrimitiveEncoding::sizeVariableInt64(this->value());
                
                return result;
            }
        };

        class ProtoInt64Collection : public ProtoNumericTypeCollection<std::int64_t, ProtoInt64>
        {
        public:
            explicit ProtoInt64Collection (std::int64_t defaultValue = 0)
            : ProtoNumericTypeCollection<std::int64_t, ProtoInt64>(defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::uint32_t remainingBytes = length;
                while (remainingBytes)
                {
                    size_t bytesParsed = 0;
                    std::int64_t numericValue = PrimitiveEncoding::parseVariableInt64(pData, &bytesParsed);

                    addValue(numericValue);

                    pData += bytesParsed;
                    remainingBytes -= bytesParsed;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeVariableInt64(protoValue.value());
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::sizeVariableInt64(protoValue.value());
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }
                
                return result;
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
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t bytesParsed = 0;
                std::uint32_t numericValue = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &bytesParsed);

                setValue(numericValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->value());

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                
                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->value());
                
                return result;
            }
        };

        class ProtoUnsignedInt32Collection : public ProtoNumericTypeCollection<std::uint32_t, ProtoUnsignedInt32>
        {
        public:
            explicit ProtoUnsignedInt32Collection (std::uint32_t defaultValue = 0)
            : ProtoNumericTypeCollection<std::uint32_t, ProtoUnsignedInt32>(defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::uint32_t remainingBytes = length;
                while (remainingBytes)
                {
                    size_t bytesParsed = 0;
                    std::uint32_t numericValue = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &bytesParsed);

                    addValue(numericValue);

                    pData += bytesParsed;
                    remainingBytes -= bytesParsed;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeVariableUnsignedInt32(protoValue.value());
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::sizeVariableUnsignedInt32(protoValue.value());
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }
                
                return result;
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
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t bytesParsed = 0;
                std::uint64_t numericValue = PrimitiveEncoding::parseVariableUnsignedInt64(pData, &bytesParsed);

                setValue(numericValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeVariableUnsignedInt64(this->value());

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                
                result += PrimitiveEncoding::sizeVariableUnsignedInt64(this->value());
                
                return result;
            }
        };

        class ProtoUnsignedInt64Collection : public ProtoNumericTypeCollection<std::uint64_t, ProtoUnsignedInt64>
        {
        public:
            explicit ProtoUnsignedInt64Collection (std::uint64_t defaultValue = 0)
            : ProtoNumericTypeCollection<std::uint64_t, ProtoUnsignedInt64>(defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::uint32_t remainingBytes = length;
                while (remainingBytes)
                {
                    size_t bytesParsed = 0;
                    std::uint64_t numericValue = PrimitiveEncoding::parseVariableUnsignedInt64(pData, &bytesParsed);

                    addValue(numericValue);

                    pData += bytesParsed;
                    remainingBytes -= bytesParsed;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeVariableUnsignedInt64(protoValue.value());
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::sizeVariableUnsignedInt64(protoValue.value());
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }
                
                return result;
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
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t bytesParsed = 0;
                std::int32_t numericValue = PrimitiveEncoding::parseVariableSignedInt32(pData, &bytesParsed);

                setValue(numericValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeVariableSignedInt32(this->value());

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                
                result += PrimitiveEncoding::sizeVariableSignedInt32(this->value());
                
                return result;
            }
        };

        class ProtoSignedInt32Collection : public ProtoNumericTypeCollection<std::int32_t, ProtoSignedInt32>
        {
        public:
            explicit ProtoSignedInt32Collection (std::int32_t defaultValue = 0)
            : ProtoNumericTypeCollection<std::int32_t, ProtoSignedInt32>(defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::uint32_t remainingBytes = length;
                while (remainingBytes)
                {
                    size_t bytesParsed = 0;
                    std::int32_t numericValue = PrimitiveEncoding::parseVariableSignedInt32(pData, &bytesParsed);

                    addValue(numericValue);

                    pData += bytesParsed;
                    remainingBytes -= bytesParsed;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeVariableSignedInt32(protoValue.value());
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::sizeVariableSignedInt32(protoValue.value());
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }
                
                return result;
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
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t bytesParsed = 0;
                std::int64_t numericValue = PrimitiveEncoding::parseVariableSignedInt64(pData, &bytesParsed);

                setValue(numericValue);

                return bytesParsed;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeVariableSignedInt64(this->value());

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                
                result += PrimitiveEncoding::sizeVariableSignedInt64(this->value());
                
                return result;
            }
        };

        class ProtoSignedInt64Collection : public ProtoNumericTypeCollection<std::int64_t, ProtoSignedInt64>
        {
        public:
            explicit ProtoSignedInt64Collection (std::int64_t defaultValue = 0)
            : ProtoNumericTypeCollection<std::int64_t, ProtoSignedInt64>(defaultValue)
            {}

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::uint32_t remainingBytes = length;
                while (remainingBytes)
                {
                    size_t bytesParsed = 0;
                    std::int64_t numericValue = PrimitiveEncoding::parseVariableSignedInt64(pData, &bytesParsed);

                    addValue(numericValue);

                    pData += bytesParsed;
                    remainingBytes -= bytesParsed;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeVariableSignedInt64(protoValue.value());
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::sizeVariableSignedInt64(protoValue.value());
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }
                
                return result;
            }
        };

        class ProtoFixed32 : public ProtoNumericType<std::int32_t>
        {
        public:
            explicit ProtoFixed32 (std::int32_t defaultValue = 0)
            : ProtoNumericType<std::int32_t>(0, defaultValue)
            {}

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x05;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                std::int32_t numericValue = PrimitiveEncoding::parseFixedInt32(pData);

                setValue(numericValue);

                return 4;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeFixedInt32(this->value());

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                
                result += 4;
                
                return result;
            }
        };

        class ProtoFixed32Collection : public ProtoNumericTypeCollection<std::int32_t, ProtoFixed32>
        {
        public:
            explicit ProtoFixed32Collection (std::int32_t defaultValue = 0)
            : ProtoNumericTypeCollection<std::int32_t, ProtoFixed32>(defaultValue)
            {}

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x02;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::uint32_t itemCount = length / 4;
                for (unsigned int i = 0; i < itemCount; ++i)
                {
                    std::int32_t numericValue = PrimitiveEncoding::parseFixedInt32(pData);

                    addValue(numericValue);

                    pData += 4;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeFixedInt32(protoValue.value());
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += 4;
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }
                
                return result;
            }
        };

        class ProtoFixed64 : public ProtoNumericType<std::int64_t>
        {
        public:
            explicit ProtoFixed64 (std::int64_t defaultValue = 0)
            : ProtoNumericType<std::int64_t>(0, defaultValue)
            {}

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x01;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                std::int64_t numericValue = PrimitiveEncoding::parseFixedInt64(pData);

                setValue(numericValue);

                return 8;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeFixedInt64(this->value());

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                
                result += 8;
                
                return result;
            }
        };

        class ProtoFixed64Collection : public ProtoNumericTypeCollection<std::int64_t, ProtoFixed64>
        {
        public:
            explicit ProtoFixed64Collection (std::int64_t defaultValue = 0)
            : ProtoNumericTypeCollection<std::int64_t, ProtoFixed64>(defaultValue)
            {}

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x02;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::uint32_t itemCount = length / 8;
                for (unsigned int i = 0; i < itemCount; ++i)
                {
                    std::int64_t numericValue = PrimitiveEncoding::parseFixedInt64(pData);

                    addValue(numericValue);

                    pData += 8;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeFixedInt64(protoValue.value());
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += 8;
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }
                
                return result;
            }
        };

        class ProtoSignedFixed32 : public ProtoFixed32
        {
        public:
            explicit ProtoSignedFixed32 (std::int32_t defaultValue = 0)
            : ProtoFixed32(defaultValue)
            {}
        };

        class ProtoSignedFixed32Collection : public ProtoNumericTypeCollection<std::int32_t, ProtoSignedFixed32>
        {
        public:
            explicit ProtoSignedFixed32Collection (std::int32_t defaultValue = 0)
            : ProtoNumericTypeCollection<std::int32_t, ProtoSignedFixed32>(defaultValue)
            {}
        };

        class ProtoSignedFixed64 : public ProtoFixed64
        {
        public:
            explicit ProtoSignedFixed64 (std::int64_t defaultValue = 0)
            : ProtoFixed64(defaultValue)
            {}
        };

        class ProtoSignedFixed64Collection : public ProtoNumericTypeCollection<std::int64_t, ProtoSignedFixed64>
        {
        public:
            explicit ProtoSignedFixed64Collection (std::int64_t defaultValue = 0)
            : ProtoNumericTypeCollection<std::int64_t, ProtoSignedFixed64>(defaultValue)
            {}
        };

        class ProtoFloat : public ProtoNumericType<float>
        {
        public:
            explicit ProtoFloat (float defaultValue = 0)
            : ProtoNumericType<float>(0, defaultValue)
            {}

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x05;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                float numericValue = PrimitiveEncoding::parseFloat(pData);

                setValue(numericValue);

                return 4;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeFloat(this->value());

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                
                result += 4;
                
                return result;
            }
        };

        class ProtoFloatCollection : public ProtoNumericTypeCollection<float, ProtoFloat>
        {
        public:
            explicit ProtoFloatCollection (float defaultValue = 0)
            : ProtoNumericTypeCollection<float, ProtoFloat>(defaultValue)
            {}

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x02;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::uint32_t itemCount = length / 4;
                for (unsigned int i = 0; i < itemCount; ++i)
                {
                    float numericValue = PrimitiveEncoding::parseFloat(pData);

                    addValue(numericValue);

                    pData += 4;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeFloat(protoValue.value());
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += 4;
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }
                
                return result;
            }
        };

        class ProtoDouble : public ProtoNumericType<double>
        {
        public:
            explicit ProtoDouble (double defaultValue = 0)
            : ProtoNumericType<double>(0, defaultValue)
            {}

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x01;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                double numericValue = PrimitiveEncoding::parseDouble(pData);

                setValue(numericValue);

                return 8;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeDouble(this->value());

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                
                result += 8;
                
                return result;
            }
        };

        class ProtoDoubleCollection : public ProtoNumericTypeCollection<double, ProtoDouble>
        {
        public:
            explicit ProtoDoubleCollection (double defaultValue = 0)
            : ProtoNumericTypeCollection<double, ProtoDouble>(defaultValue)
            {}

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x02;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::uint32_t itemCount = length / 8;
                for (unsigned int i = 0; i < itemCount; ++i)
                {
                    double numericValue = PrimitiveEncoding::parseDouble(pData);

                    addValue(numericValue);

                    pData += 8;
                }

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                for (auto & protoValue: *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += PrimitiveEncoding::serializeDouble(protoValue.value());
                    }
                }
                if (!result.empty())
                {
                    result = PrimitiveEncoding::serializeVariableUnsignedInt32(this->key()) +
                        PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +
                        result;
                }

                return result;
            }

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & protoValue : *this->collection())
                {
                    if (protoValue.hasValue())
                    {
                        result += 8;
                    }
                }

                if (result != 0)
                {
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                    result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());
                }
                
                return result;
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

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x02;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                if (pData == nullptr)
                {
                    throw std::invalid_argument("pData cannot be null.");
                }

                size_t lengthBytesParsed = 0;
                std::uint32_t length = PrimitiveEncoding::parseVariableUnsignedInt32(pData, &lengthBytesParsed);
                pData += lengthBytesParsed;

                std::string stringValue;
                for (unsigned int i = 0; i < length; ++i)
                {
                    stringValue += *pData;
                    ++pData;
                }
                setValue(stringValue);

                return lengthBytesParsed + length;
            }

            virtual std::string serialize () const
            {
                std::string result;

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(this->key());

                result += PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(mValue.size()));

                result += mValue;
                
                return result;
            }

            virtual size_t size () const
            {
                size_t result = mValue.size();

                if (!this->hasValue())
                {
                    return result;
                }

                result += PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));
                result += PrimitiveEncoding::sizeVariableUnsignedInt32(this->key());

                return result;
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

        template <typename ProtoType>
        class ProtoStringTypeCollection : public ProtoBase
        {
        public:
            virtual const std::vector<std::shared_ptr<ProtoType>> * collection () const
            {
                return &mCollection;
            }

            virtual std::vector<std::shared_ptr<ProtoType>> * mutableCollection ()
            {
                return &mCollection;
            }

            virtual void addValue (const std::string & value)
            {
                std::shared_ptr<ProtoType> valueType(new ProtoType(mValueDefault));

                valueType.setIndex(index());
                valueType.setValue(value);

                mCollection.push_back(valueType);
            }

            virtual unsigned int key () const
            {
                return (index() << 3) | 0x02;
            }

            virtual size_t parse (const unsigned char * pData)
            {
                std::shared_ptr<ProtoType> value(new ProtoType());
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

            virtual size_t size () const
            {
                size_t result = 0;

                for (auto & value : mCollection)
                {
                    result += value->size();
                }

                return result;
            }

            virtual bool hasValue () const
            {
                return !mCollection.empty();
            }

            virtual void clearValue ()
            {
                mCollection.clear();
            }

            virtual bool valid () const
            {
                return true;
            }

        protected:
            ProtoStringTypeCollection (const std::string & defaultValue)
            : mValueDefault(defaultValue)
            {}

        private:
            std::vector<std::shared_ptr<ProtoType>> mCollection;
            std::string mValueDefault;
        };

        class ProtoString : public ProtoStringType
        {
        public:
            explicit ProtoString (const std::string & defaultValue = "")
            : ProtoStringType("", defaultValue)
            {}
        };

        class ProtoStringCollection : public ProtoStringTypeCollection<ProtoString>
        {
        public:
            explicit ProtoStringCollection (const std::string & defaultValue = "")
            : ProtoStringTypeCollection<ProtoString>(defaultValue)
            {}
        };

        class ProtoBytes : public ProtoStringType
        {
        public:
            explicit ProtoBytes (const std::string & defaultValue = "")
            : ProtoStringType("", defaultValue)
            {}
        };

        class ProtoBytesCollection : public ProtoStringTypeCollection<ProtoBytes>
        {
        public:
            explicit ProtoBytesCollection (const std::string & defaultValue = "")
            : ProtoStringTypeCollection<ProtoBytes>(defaultValue)
            {}
        };
    }
}
)MuddledManaged";