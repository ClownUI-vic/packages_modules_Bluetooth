# Copyright 2024 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from pairing.br_edr.legacy.tests import BREDRLegacyTestClass
from pairing.br_edr.misc.service_access_tests import ServiceAccessTempBondingTest

from pairing.br_edr.ssp.display_output_and_yes_no_input.tests import BREDRDisplayYesNoTestClass
from pairing.br_edr.ssp.display_output_only.tests import BREDRDisplayOnlyTestClass
from pairing.br_edr.ssp.no_output_no_input.tests import BREDRNoOutputNoInputTestClass

from pairing.smp_test import SmpTest

_test_class_list = [
    BREDRDisplayYesNoTestClass,
    BREDRDisplayOnlyTestClass,
    BREDRNoOutputNoInputTestClass,
    BREDRLegacyTestClass,
    ServiceAccessTempBondingTest,
    SmpTest,
]
