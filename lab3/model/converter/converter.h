#pragma once

#include "exceptions/converter_exception.h"
#include <cstdint>
#include <memory>
#include <string>
#include <sys/types.h>
#include <tuple>
#include <vector>
#include <map>
#include <unordered_set>

using std::string, std::vector, std::tuple, std::make_shared, std::shared_ptr, std::map, std::unordered_set;

namespace converter {
    struct ConverterDTO {
        uint16_t sampleRate;
        uint16_t numChannels;
        vector<vector<int16_t>> samples;
    };

    class ConverterInterface {
        public:
            ConverterInterface() = default;
            virtual ~ConverterInterface() = default;
            virtual void ChangeAudioData(const string& args, ConverterDTO& info) = 0;
    };

    using ConverterPtr = shared_ptr<ConverterInterface>;

    class MixConverter final : public ConverterInterface {
        private:
            void ParseArguments(const string& args, ConverterDTO& info, tuple<unsigned, unsigned>& times, vector<unsigned>& streams);
        public:
            MixConverter() = default;
            ~MixConverter() = default;
            void ChangeAudioData(const string& args, ConverterDTO& info) override;
    };

    class MuteConverter final : public ConverterInterface {
        private:
            void ParseArguments(const string& args, ConverterDTO& info, tuple<unsigned, unsigned>& times, unsigned& stream);
        public:
            MuteConverter() = default;
            ~MuteConverter() = default;
            void ChangeAudioData(const string& args, ConverterDTO& info) override;
    };

    class VolumeConverter final : public ConverterInterface {
        private:
            void ParseArguments(const string& args, ConverterDTO& info, tuple<unsigned, unsigned>& times, unsigned& stream, double& multiplier);
        public:
            VolumeConverter() = default;
            ~VolumeConverter() = default;
            void ChangeAudioData(const string& args, ConverterDTO& info) override;
    };

    class AbstractConverterCreator {
        public:
            AbstractConverterCreator() = default;
            virtual ~AbstractConverterCreator() = default;
            virtual shared_ptr<ConverterInterface> Create() = 0;
    };

    template <typename Converter>
    class ConverterCreator final : public AbstractConverterCreator {
        public:
            ConverterCreator() = default;
            ~ConverterCreator() = default;
            virtual shared_ptr<ConverterInterface> Create() {
                return make_shared<Converter>();
            }
    };

    class ConverterFactory {
        protected:
            using FactoryPtr = shared_ptr<AbstractConverterCreator>;
            map<string, FactoryPtr> converters_;

            ConverterFactory& operator = (const ConverterFactory&) = delete;

        public:
            ConverterFactory() = default;
            ~ConverterFactory() = default;

            template <typename Converter>
            void Add(const string& id) {
                if (converters_.find(id) == converters_.end()) {
                    converters_[id] = make_shared<ConverterCreator<Converter>>();
                }
            }

            shared_ptr<ConverterInterface> CreateConverter(const string& id) {
                if (converters_.find(id) == converters_.end()) {
                    throw converterException::ConverterCreateException(id);
                }
                return converters_[id]->Create();
            }
    };
}