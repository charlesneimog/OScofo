#include <vector>

#include "../OScofo.hpp" // Assuming this header file defines your OScofo class
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(_OScofo, m) {
    py::class_<OScofo>(m, "OScofo")
        .def(py::init<float, float, float>())
        .def("ParseScore", &OScofo::ParseScore)
        .def("GetLiveBPM", &OScofo::GetLiveBPM)
        .def("SetPitchTemplateSigma", &OScofo::SetPitchTemplateSigma)
        .def("SetHarmonics", &OScofo::SetHarmonics)
        .def("SetTimeAccumFactor", &OScofo::SetTimeAccumFactor)
        .def("SetTimeCouplingStrength", &OScofo::SetTimeCouplingStrength)
        .def("SetdBTreshold", &OScofo::SetdBTreshold)
        .def("SetTunning", &OScofo::SetTunning)
        .def("SetCurrentEvent", &OScofo::SetCurrentEvent)
        .def("ScoreIsLoaded", &OScofo::ScoreIsLoaded)
        .def("GetEventIndex", &OScofo::GetEventIndex)
        .def("GetError", &OScofo::GetError)
        .def("ProcessBlock", [](OScofo &self, py::array_t<double> Audio) {
            py::buffer_info bufInfo = Audio.request();
            if (bufInfo.ndim != 1) {
                throw std::runtime_error("Input array must be 1-dimensional");
            }
            std::vector<double> CppAudio(static_cast<double *>(bufInfo.ptr),
                                         static_cast<double *>(bufInfo.ptr) + bufInfo.shape[0]);

            bool result = self.ProcessBlock(CppAudio);
            return result;
        });
}
