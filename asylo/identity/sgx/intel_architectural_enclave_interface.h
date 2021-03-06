/*
 *
 * Copyright 2019 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef ASYLO_IDENTITY_SGX_INTEL_ARCHITECTURAL_ENCLAVE_INTERFACE_H_
#define ASYLO_IDENTITY_SGX_INTEL_ARCHITECTURAL_ENCLAVE_INTERFACE_H_

#include <cstdint>
#include <string>

#include "absl/types/span.h"
#include "asylo/crypto/util/bytes.h"
#include "asylo/identity/sgx/identity_key_management_structs.h"
#include "asylo/util/status.h"

namespace asylo {
namespace sgx {

// IntelArchitecturalEnclaveInterface defines functions for interfacing with
// Intel's Architectural Enclaves. This interface is a lightweight wrapper
// around the APIs exposed from Intel's Data Center Attestation Primitives
// (DCAP) library. These APIs, however, use Asylo's representations of SGX
// architectural structures rather than representations from Intel's SGX SDK and
// DCAP.
class IntelArchitecturalEnclaveInterface {
 public:
  virtual ~IntelArchitecturalEnclaveInterface() = default;

  // Provisioning Certification Enclave (PCE)

  // Populates |targetinfo| with the TARGETINFO and |pce_svn| with the PCE SVN
  // of the PCE in the current local environment.
  virtual Status GetPceTargetinfo(Targetinfo *targetinfo,
                                  uint16_t *pce_svn) = 0;

  // Gets information about the PCE as well as the Platform Provisioning ID
  // (PPID) in the current local environment.
  //
  // The caller must provide the following:
  //
  // * |crypto_suite| is the asymmetric crypto suite used to encrypt the PPID.
  // * |ppid_encryption_key| is an asymmetric encryption key matching the
  //   provided |crypto_suite| that is used to encrypt the PPID.
  // * |report| is an SGX hardware REPORT that must meet the following
  //   requirements:
  //   * The REPORT is targeted at the PCE.
  //   * The PROVISION_KEY bit in REPORT.ATTRIBUTES is set.
  //   * REPORT.REPORTDATA is:
  //     SHA256HASH(pub key modulus || pub key exponent || crypto suite) || 0^32
  //
  // Additionally, the caller should ensure that the length of |ppid_encrypted|
  // is at least the expected ciphertext length. For RSA encryption schemes, it
  // must be pre-sized to at least the length of the public-key modulus.
  //
  // The following values are populated on success:
  //
  // * |ppid_encrypted| is populated with the encrypted PPID.
  // * |pce_svn| is set to the PCE SVN of the PCE. This is the same as the
  //   ISVSVN of the PCE.
  // * |pce_id| is set to the PCE ID of the PCE. This value is an identifier for
  //   the PPID-generation algorithm.
  // * |signature_scheme| is set to the signature scheme used by the PCE's PCK.
  virtual Status GetPceInfo(const Report &report,
                            absl::Span<const uint8_t> ppid_encryption_key,
                            uint8_t crypto_suite, std::string *ppid_encrypted,
                            uint16_t *pce_svn, uint16_t *pce_id,
                            uint8_t *signature_scheme) = 0;

  // Requests the PCE to sign the given |report| with the PCK corresponding to
  // |target_pce_svn| and |target_cpusvn|. The resulting signature is written to
  // |signature|.
  //
  // The caller must ensure that the length of |signature| is at least the size
  // of the expected signature length. The supported signature scheme can be
  // retrieved through the GetPceInfo() method.
  virtual Status PceSignReport(const Report &report, uint16_t target_pce_svn,
                               UnsafeBytes<kCpusvnSize> target_cpu_svn,
                               std::string *signature) = 0;
};

}  // namespace sgx
}  // namespace asylo

#endif  // ASYLO_IDENTITY_SGX_INTEL_ARCHITECTURAL_ENCLAVE_INTERFACE_H_
