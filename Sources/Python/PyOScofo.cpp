#include <vector>

#include <OScofo.hpp>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(_OScofo, m) {

    py::class_<OScofo::OScofo>(m, "OScofo")
        .def(py::init<float, float, float>())
        // Score
        .def("ParseScore", &OScofo::OScofo::ParseScore)

        // Config
        .def("SetPitchTemplateSigma", &OScofo::OScofo::SetPitchTemplateSigma)
        .def("SetHarmonics", &OScofo::OScofo::SetHarmonics)
        .def("SetdBTreshold", &OScofo::OScofo::SetdBTreshold)
        .def("SetTunning", &OScofo::OScofo::SetTunning)
        .def("SetCurrentEvent", &OScofo::OScofo::SetCurrentEvent)

        // Get Info
        .def("GetLiveBPM", &OScofo::OScofo::GetLiveBPM)
        .def("GetEventIndex", &OScofo::OScofo::GetEventIndex)
        .def("GetError", &OScofo::OScofo::GetError)
        .def("GetStates", &OScofo::OScofo::GetStates)
        .def("GetPitchTemplate", &OScofo::OScofo::GetPitchTemplate)

        // Process
        .def("ProcessBlock", [](OScofo::OScofo &self, py::array_t<double> Audio) {
            py::buffer_info bufInfo = Audio.request();
            if (bufInfo.ndim != 1) {
                throw std::runtime_error("Input array must be 1-dimensional");
            }
            std::vector<double> CppAudio(static_cast<double *>(bufInfo.ptr), static_cast<double *>(bufInfo.ptr) + bufInfo.shape[0]);

            bool result = self.ProcessBlock(CppAudio);
            return result;
        });

    // State Class
    py::class_<OScofo::MacroState>(m, "State")
        .def(py::init<>()) // Default constructor
        .def_readwrite("Index", &OScofo::MacroState::Index)
        .def_readwrite("Position", &OScofo::MacroState::ScorePos)
        .def_readwrite("Type", &OScofo::MacroState::Type)
        .def_readwrite("Markov", &OScofo::MacroState::Markov)
        .def_readwrite("Freqs", &OScofo::MacroState::Freqs)
        .def_readwrite("KLDiv", &OScofo::MacroState::Obs)
        .def_readwrite("Forward", &OScofo::MacroState::Forward)
        .def_readwrite("BPMExpected", &OScofo::MacroState::BPMExpected)
        .def_readwrite("BPMObserved", &OScofo::MacroState::BPMObserved)
        .def_readwrite("OnsetExpected", &OScofo::MacroState::OnsetExpected)
        .def_readwrite("OnsetObserved", &OScofo::MacroState::OnsetObserved)
        .def_readwrite("PhaseExpected", &OScofo::MacroState::PhaseExpected)
        .def_readwrite("PhaseObserved", &OScofo::MacroState::PhaseObserved)
        .def_readwrite("IOIPhiN", &OScofo::MacroState::IOIPhiN)
        .def_readwrite("IOIHatPhiN", &OScofo::MacroState::IOIHatPhiN)
        .def_readwrite("Duration", &OScofo::MacroState::Duration)
        .def_readwrite("Line", &OScofo::MacroState::Line)
        .def("__repr__", &OScofo::MacroState::__repr__)
        .def("__str__", &OScofo::MacroState::__repr__);
}
