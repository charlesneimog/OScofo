#include <vector>

#include <OScofo.hpp> // Assuming this header file defines your OScofo class
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(_OScofo, m) {

    py::class_<OScofo>(m, "OScofo")
        .def(py::init<float, float, float>())
        // Init
        .def("ParseScore", &OScofo::ParseScore)

        // Config
        .def("SetPitchTemplateSigma", &OScofo::SetPitchTemplateSigma)
        .def("SetHarmonics", &OScofo::SetHarmonics)
        .def("SetTimeAccumFactor", &OScofo::SetTimeAccumFactor)
        .def("SetTimeCouplingStrength", &OScofo::SetTimeCouplingStrength)
        .def("SetdBTreshold", &OScofo::SetdBTreshold)
        .def("SetTunning", &OScofo::SetTunning)
        .def("SetCurrentEvent", &OScofo::SetCurrentEvent)

        // Get Info
        .def("GetLiveBPM", &OScofo::GetLiveBPM)
        .def("GetEventIndex", &OScofo::GetEventIndex)
        .def("GetError", &OScofo::GetError)
        .def("GetStates", &OScofo::GetStates)
        .def("GetPitchTemplate", &OScofo::GetPitchTemplate)

        // Process
        .def("ProcessBlock", [](OScofo &self, py::array_t<double> Audio) {
            py::buffer_info bufInfo = Audio.request();
            if (bufInfo.ndim != 1) {
                throw std::runtime_error("Input array must be 1-dimensional");
            }
            std::vector<double> CppAudio(static_cast<double *>(bufInfo.ptr), static_cast<double *>(bufInfo.ptr) + bufInfo.shape[0]);

            bool result = self.ProcessBlock(CppAudio);
            return result;
        });

    // State Class
    py::class_<State>(m, "State")
        .def(py::init<>()) // Default constructor
        .def_readwrite("Index", &State::Index)
        .def_readwrite("Position", &State::Position)
        .def_readwrite("Type", &State::Type)
        .def_readwrite("Markov", &State::Markov)
        .def_readwrite("Freqs", &State::Freqs)
        .def_readwrite("KLDiv", &State::Obs)
        .def_readwrite("AlphaT", &State::AlphaT)
        .def_readwrite("BPMExpected", &State::BPMExpected)
        .def_readwrite("BPMObserved", &State::BPMObserved)
        .def_readwrite("OnsetExpected", &State::OnsetExpected)
        .def_readwrite("OnsetObserved", &State::OnsetObserved)
        .def_readwrite("PhaseExpected", &State::PhaseExpected)
        .def_readwrite("PhaseObserved", &State::PhaseObserved)
        .def_readwrite("IOIPhiN", &State::IOIPhiN)
        .def_readwrite("IOIHatPhiN", &State::IOIHatPhiN)
        .def_readwrite("Duration", &State::Duration)
        .def_readwrite("Valid", &State::Valid)
        .def_readwrite("Line", &State::Line)
        .def_readwrite("Error", &State::Error)
        .def("__repr__", &State::to_string)
        .def("__str__", &State::to_string);
}
