const string Protocol::CodeGeneratorCPP::mProtoBaseHeaderFileTemplate =

R"MuddledManaged(namespace MuddledManaged
{
    namespace Protocol
    {
        int sizeVarInt (unsigned long long value)
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

        int sizeIndex (unsigned long long index)
        {
            return sizeVarInt(index << 3);
        }

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

            virtual void parse (const std::string & data) = 0;

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

            virtual void parse (const std::string & data);

            virtual std::string serialize () const;

            virtual size_t size () const
            {
                return sizeVarInt(mValue);
            }

        protected:
            ProtoNumericType (NumericType defaultValue)
            : mValue(defaultValue), mValueDefault(defaultValue)
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
            : ProtoNumericType<EnumType>(defaultValue)
            {}
        };

        class ProtoBool : public ProtoNumericType<bool>
        {
        public:
            explicit ProtoBool (bool defaultValue = false)
            : ProtoNumericType<bool>(defaultValue)
            {}
        };

        class ProtoInt32 : public ProtoNumericType<std::int32_t>
        {
        public:
            explicit ProtoInt32 (std::int32_t defaultValue = 0)
            : ProtoNumericType<std::int32_t>(defaultValue)
            {}
        };

        class ProtoInt64 : public ProtoNumericType<std::int64_t>
        {
        public:
            explicit ProtoInt64 (std::int64_t defaultValue = 0)
            : ProtoNumericType<std::int64_t>(defaultValue)
            {}
        };

        class ProtoUnsignedInt32 : public ProtoNumericType<std::uint32_t>
        {
        public:
            explicit ProtoUnsignedInt32 (std::uint32_t defaultValue = 0)
            : ProtoNumericType<std::uint32_t>(defaultValue)
            {}
        };

        class ProtoUnsignedInt64 : public ProtoNumericType<std::uint64_t>
        {
        public:
            explicit ProtoUnsignedInt64 (std::uint64_t defaultValue = 0)
            : ProtoNumericType<std::uint64_t>(defaultValue)
            {}
        };

        class ProtoSignedInt32 : public ProtoNumericType<std::int32_t>
        {
        public:
            explicit ProtoSignedInt32 (std::int32_t defaultValue = 0)
            : ProtoNumericType<std::int32_t>(defaultValue)
            {}

            virtual void parse (const std::string & data);

            virtual std::string serialize () const;
        };

        class ProtoSignedInt64 : public ProtoNumericType<std::int64_t>
        {
        public:
            explicit ProtoSignedInt64 (std::int64_t defaultValue = 0)
            : ProtoNumericType<std::int64_t>(defaultValue)
            {}

            virtual void parse (const std::string & data);

            virtual std::string serialize () const;
        };

        class ProtoFixed32 : public ProtoNumericType<std::int32_t>
        {
        public:
            explicit ProtoFixed32 (std::int32_t defaultValue = 0)
            : ProtoNumericType<std::int32_t>(defaultValue)
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
            : ProtoNumericType<std::int64_t>(defaultValue)
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
            : ProtoNumericType<float>(defaultValue)
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
            : ProtoNumericType<double>(defaultValue)
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
            ProtoStringType (const std::string & defaultValue)
            : mValueDefault(defaultValue)
            {}
            
        private:
            std::string mValue;
            std::string mValueDefault;
        };
        
        class ProtoString : public ProtoStringType
        {
        public:
            explicit ProtoString (const std::string & defaultValue = "")
            : ProtoStringType(defaultValue)
            {}
        };
        
        class ProtoBytes : public ProtoStringType
        {
        public:
            explicit ProtoBytes ()
            : ProtoStringType("")
            {}
        };
    }
}
)MuddledManaged";