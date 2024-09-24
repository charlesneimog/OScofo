#include <vector>

#include <OScofo.hpp>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(_OScofo, m) {

    py::class_<OScofo>(m, "OScofo")
        .def(py::init<float, float, float>())
        // Score
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
        .def("GetGaussianTimeLine", &OScofo::GaussianProbTimeOnset)

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
    py::class_<MacroState>(m, "State")
        .def(py::init<>()) // Default constructor
        .def_readwrite("Index", &MacroState::Index)
        .def_readwrite("Position", &MacroState::ScorePos)
        .def_readwrite("Type", &MacroState::Type)
        .def_readwrite("Markov", &MacroState::Markov)
        .def_readwrite("Freqs", &MacroState::Freqs)
        .def_readwrite("KLDiv", &MacroState::Obs)
        .def_readwrite("Forward", &MacroState::Forward)
        .def_readwrite("BPMExpected", &MacroState::BPMExpected)
        .def_readwrite("BPMObserved", &MacroState::BPMObserved)
        .def_readwrite("OnsetExpected", &MacroState::OnsetExpected)
        .def_readwrite("OnsetObserved", &MacroState::OnsetObserved)
        .def_readwrite("PhaseExpected", &MacroState::PhaseExpected)
        .def_readwrite("PhaseObserved", &MacroState::PhaseObserved)
        .def_readwrite("IOIPhiN", &MacroState::IOIPhiN)
        .def_readwrite("IOIHatPhiN", &MacroState::IOIHatPhiN)
        .def_readwrite("Duration", &MacroState::Duration)
        .def_readwrite("Line", &MacroState::Line)
        .def("__repr__", &MacroState::__repr__)
        .def("__str__", &MacroState::__repr__);
}
